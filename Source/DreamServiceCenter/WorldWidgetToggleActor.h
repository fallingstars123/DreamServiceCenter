// Copyright (c) 2026. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WorldWidgetToggleActor.generated.h"

class APawn;
class APlayerController;
class USceneComponent;
class USphereComponent;
class UStaticMeshComponent;
class UWidgetComponent;

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FWorldWidgetToggleEvent);

/**
 * Placeable actor that toggles a world-space widget with F while the local player
 * is inside its interaction sphere. The astronaut's watch menu is temporarily
 * hidden while this actor menu is open; the viewport HUD is left untouched.
 */
UCLASS(Blueprintable)
class DREAMSERVICECENTER_API AWorldWidgetToggleActor : public AActor
{
	GENERATED_BODY()

public:
	AWorldWidgetToggleActor();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	/** Toggle the world widget. This can also be called from Blueprint. */
	UFUNCTION(BlueprintCallable, Category = "World Widget")
	void ToggleWorldWidget();

	UFUNCTION(BlueprintCallable, Category = "World Widget")
	void OpenWorldWidget();

	UFUNCTION(BlueprintCallable, Category = "World Widget")
	void CloseWorldWidget();

	UFUNCTION(BlueprintPure, Category = "World Widget")
	bool IsWorldWidgetOpen() const { return bWorldWidgetOpen; }

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USceneComponent> SceneRoot;

	/** Assign the actor's visible Static Mesh asset on this component. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UStaticMeshComponent> StaticMesh;

	/** Player must overlap this sphere before F is accepted. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<USphereComponent> InteractionSphere;

	/** Assign your Widget Blueprint class here. It always renders in World space. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UWidgetComponent> WorldWidget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction", meta = (ClampMin = "1.0", UIMin = "50.0"))
	float InteractionRadius = 250.0f;

	/** Close and restore the watch menu when the player leaves the interaction sphere. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Interaction")
	bool bCloseWhenPlayerLeavesRange = true;

	/** Hide BP_Astronaut's WatchMenuPanel while this actor's widget is open. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Watch Menu")
	bool bHidePlayerWatchMenuWhileOpen = true;

	/** Component variable name used by BP_Astronaut for the pictured watch menu. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Watch Menu")
	FName WatchMenuComponentName = TEXT("WatchMenuPanel");

	UPROPERTY(BlueprintAssignable, Category = "World Widget")
	FWorldWidgetToggleEvent OnWorldWidgetOpened;

	UPROPERTY(BlueprintAssignable, Category = "World Widget")
	FWorldWidgetToggleEvent OnWorldWidgetClosed;

protected:
	UFUNCTION()
	void HandleInteractionBeginOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

	UFUNCTION()
	void HandleInteractionEndOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComponent,
		int32 OtherBodyIndex);

private:
	struct FSavedWatchMenuState
	{
		TWeakObjectPtr<USceneComponent> Component;
		bool bWasVisible = false;
		TWeakObjectPtr<AActor> ChildActor;
		bool bChildActorWasHiddenInGame = false;
	};

	void EnableInteractionInput(APlayerController* PlayerController, APawn* PlayerPawn);
	void DisableInteractionInput();
	void HidePlayerWatchMenu();
	void RestorePlayerWatchMenu();
	USceneComponent* FindPlayerWatchMenu(APawn* PlayerPawn) const;
	bool IsLocalPlayerPawn(const APawn* Pawn, APlayerController*& OutPlayerController) const;

	bool bWorldWidgetOpen = false;
	bool bInputBindingCreated = false;
	bool bHasSavedWatchMenuState = false;
	TWeakObjectPtr<APawn> OverlappingPlayerPawn;
	TWeakObjectPtr<APlayerController> InteractingPlayerController;
	FSavedWatchMenuState SavedWatchMenuState;
};
