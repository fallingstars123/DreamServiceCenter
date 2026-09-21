// Copyright (c) 2026. All rights reserved.

#include "WorldWidgetToggleActor.h"

#include "Components/ChildActorComponent.h"
#include "Components/InputComponent.h"
#include "Components/SceneComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/PlayerController.h"
#include "InputCoreTypes.h"

AWorldWidgetToggleActor::AWorldWidgetToggleActor()
{
	PrimaryActorTick.bCanEverTick = false;
	InputPriority = 100;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(SceneRoot);

	InteractionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("InteractionSphere"));
	InteractionSphere->SetupAttachment(SceneRoot);
	InteractionSphere->SetSphereRadius(InteractionRadius);
	InteractionSphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionSphere->SetCollisionObjectType(ECC_WorldDynamic);
	InteractionSphere->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractionSphere->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	InteractionSphere->SetGenerateOverlapEvents(true);

	WorldWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("WorldWidget"));
	WorldWidget->SetupAttachment(SceneRoot);
	WorldWidget->SetWidgetSpace(EWidgetSpace::World);
	WorldWidget->SetDrawAtDesiredSize(true);
	WorldWidget->SetTwoSided(true);
	WorldWidget->SetVisibility(false);
	WorldWidget->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AWorldWidgetToggleActor::BeginPlay()
{
	Super::BeginPlay();

	InteractionSphere->SetSphereRadius(InteractionRadius, true);
	WorldWidget->SetWidgetSpace(EWidgetSpace::World);
	WorldWidget->SetVisibility(false);
	bWorldWidgetOpen = false;

	InteractionSphere->OnComponentBeginOverlap.AddDynamic(
		this,
		&AWorldWidgetToggleActor::HandleInteractionBeginOverlap);
	InteractionSphere->OnComponentEndOverlap.AddDynamic(
		this,
		&AWorldWidgetToggleActor::HandleInteractionEndOverlap);
}

void AWorldWidgetToggleActor::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	RestorePlayerWatchMenu();
	DisableInteractionInput();
	Super::EndPlay(EndPlayReason);
}

void AWorldWidgetToggleActor::ToggleWorldWidget()
{
	if (bWorldWidgetOpen)
	{
		CloseWorldWidget();
	}
	else
	{
		OpenWorldWidget();
	}
}

void AWorldWidgetToggleActor::OpenWorldWidget()
{
	if (bWorldWidgetOpen || !WorldWidget)
	{
		return;
	}

	if (bHidePlayerWatchMenuWhileOpen)
	{
		HidePlayerWatchMenu();
	}

	bWorldWidgetOpen = true;
	WorldWidget->SetVisibility(true);
	OnWorldWidgetOpened.Broadcast();
}

void AWorldWidgetToggleActor::CloseWorldWidget()
{
	if (!bWorldWidgetOpen)
	{
		return;
	}

	bWorldWidgetOpen = false;
	if (WorldWidget)
	{
		WorldWidget->SetVisibility(false);
	}
	RestorePlayerWatchMenu();
	OnWorldWidgetClosed.Broadcast();
}

void AWorldWidgetToggleActor::HandleInteractionBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	APawn* PlayerPawn = Cast<APawn>(OtherActor);
	APlayerController* PlayerController = nullptr;
	if (!IsLocalPlayerPawn(PlayerPawn, PlayerController))
	{
		return;
	}

	EnableInteractionInput(PlayerController, PlayerPawn);
}

void AWorldWidgetToggleActor::HandleInteractionEndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex)
{
	APawn* PlayerPawn = Cast<APawn>(OtherActor);
	if (!PlayerPawn || PlayerPawn != OverlappingPlayerPawn.Get())
	{
		return;
	}

	// A pawn can have several overlapping primitive components. Only deactivate after
	// the pawn itself has completely left the sphere.
	if (InteractionSphere && InteractionSphere->IsOverlappingActor(PlayerPawn))
	{
		return;
	}

	if (bCloseWhenPlayerLeavesRange)
	{
		CloseWorldWidget();
	}
	DisableInteractionInput();
}

void AWorldWidgetToggleActor::EnableInteractionInput(
	APlayerController* PlayerController,
	APawn* PlayerPawn)
{
	if (!PlayerController || !PlayerPawn)
	{
		return;
	}

	OverlappingPlayerPawn = PlayerPawn;
	InteractingPlayerController = PlayerController;
	EnableInput(PlayerController);

	if (InputComponent && !bInputBindingCreated)
	{
		FInputKeyBinding& ToggleBinding = InputComponent->BindKey(
			EKeys::F,
			IE_Pressed,
			this,
			&AWorldWidgetToggleActor::ToggleWorldWidget);
		ToggleBinding.bConsumeInput = true;
		ToggleBinding.bExecuteWhenPaused = false;
		bInputBindingCreated = true;
	}
}

void AWorldWidgetToggleActor::DisableInteractionInput()
{
	if (APlayerController* PlayerController = InteractingPlayerController.Get())
	{
		DisableInput(PlayerController);
	}
	InteractingPlayerController.Reset();
	OverlappingPlayerPawn.Reset();
}

void AWorldWidgetToggleActor::HidePlayerWatchMenu()
{
	RestorePlayerWatchMenu();

	APawn* PlayerPawn = OverlappingPlayerPawn.Get();
	if (!PlayerPawn)
	{
		if (APlayerController* PlayerController = InteractingPlayerController.Get())
		{
			PlayerPawn = PlayerController->GetPawn();
		}
	}

	USceneComponent* WatchMenu = FindPlayerWatchMenu(PlayerPawn);
	if (!WatchMenu)
	{
		return;
	}

	SavedWatchMenuState.Component = WatchMenu;
	SavedWatchMenuState.bWasVisible = WatchMenu->IsVisible();
	SavedWatchMenuState.ChildActor.Reset();
	SavedWatchMenuState.bChildActorWasHiddenInGame = false;

	if (UChildActorComponent* ChildActorComponent = Cast<UChildActorComponent>(WatchMenu))
	{
		if (AActor* ChildActor = ChildActorComponent->GetChildActor())
		{
			SavedWatchMenuState.ChildActor = ChildActor;
			SavedWatchMenuState.bChildActorWasHiddenInGame = ChildActor->IsHidden();
			ChildActor->SetActorHiddenInGame(true);
		}
	}

	WatchMenu->SetVisibility(false, true);
	bHasSavedWatchMenuState = true;
}

void AWorldWidgetToggleActor::RestorePlayerWatchMenu()
{
	if (!bHasSavedWatchMenuState)
	{
		return;
	}

	if (USceneComponent* WatchMenu = SavedWatchMenuState.Component.Get())
	{
		WatchMenu->SetVisibility(SavedWatchMenuState.bWasVisible, true);
	}
	if (AActor* ChildActor = SavedWatchMenuState.ChildActor.Get())
	{
		ChildActor->SetActorHiddenInGame(SavedWatchMenuState.bChildActorWasHiddenInGame);
	}

	SavedWatchMenuState = FSavedWatchMenuState();
	bHasSavedWatchMenuState = false;
}

USceneComponent* AWorldWidgetToggleActor::FindPlayerWatchMenu(APawn* PlayerPawn) const
{
	if (!PlayerPawn || WatchMenuComponentName.IsNone())
	{
		return nullptr;
	}

	const FString DesiredName = WatchMenuComponentName.ToString();
	const FString GeneratedNamePrefix = DesiredName + TEXT("_");
	TArray<USceneComponent*> SceneComponents;
	PlayerPawn->GetComponents<USceneComponent>(SceneComponents);

	for (USceneComponent* Component : SceneComponents)
	{
		if (!IsValid(Component))
		{
			continue;
		}

		const FString ComponentName = Component->GetName();
		if (Component->GetFName() == WatchMenuComponentName
			|| ComponentName.StartsWith(GeneratedNamePrefix))
		{
			return Component;
		}
	}

	return nullptr;
}

bool AWorldWidgetToggleActor::IsLocalPlayerPawn(
	const APawn* Pawn,
	APlayerController*& OutPlayerController) const
{
	OutPlayerController = Pawn ? Cast<APlayerController>(Pawn->GetController()) : nullptr;
	return Pawn != nullptr
		&& OutPlayerController != nullptr
		&& OutPlayerController->IsLocalController();
}
