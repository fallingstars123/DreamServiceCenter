// Copyright (c) 2026. All rights reserved.

#include "SurfaceGravityFieldVolume.h"

#include "Components/BoxComponent.h"
#include "CustomGravityComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "SurfaceGravityBlueprintLibrary.h"

ASurfaceGravityFieldVolume::ASurfaceGravityFieldVolume()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	PrimaryActorTick.TickGroup = TG_PrePhysics;

	GravityBounds = CreateDefaultSubobject<UBoxComponent>(TEXT("GravityBounds"));
	SetRootComponent(GravityBounds);
	GravityBounds->SetBoxExtent(FVector(20000.0f, 20000.0f, 8000.0f));
	GravityBounds->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	GravityBounds->SetCollisionObjectType(ECC_WorldDynamic);
	GravityBounds->SetCollisionResponseToAllChannels(ECR_Ignore);
	GravityBounds->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	GravityBounds->SetGenerateOverlapEvents(true);
	GravityBounds->SetHiddenInGame(true);
}

void ASurfaceGravityFieldVolume::BeginPlay()
{
	Super::BeginPlay();

	GravityBounds->OnComponentBeginOverlap.AddDynamic(
		this,
		&ASurfaceGravityFieldVolume::HandleBeginOverlap);
	GravityBounds->OnComponentEndOverlap.AddDynamic(
		this,
		&ASurfaceGravityFieldVolume::HandleEndOverlap);

	TArray<AActor*> InitiallyOverlapping;
	GravityBounds->GetOverlappingActors(InitiallyOverlapping, ACharacter::StaticClass());
	for (AActor* Actor : InitiallyOverlapping)
	{
		if (ACharacter* Character = Cast<ACharacter>(Actor))
		{
			HandleBeginOverlap(GravityBounds, Character, nullptr, INDEX_NONE, false, FHitResult());
		}
	}
}

void ASurfaceGravityFieldVolume::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (!bAutomaticSurfaceGravity)
	{
		return;
	}

	for (int32 Index = CharactersInside.Num() - 1; Index >= 0; --Index)
	{
		ACharacter* Character = CharactersInside[Index].Get();
		if (!IsValid(Character))
		{
			CharactersInside.RemoveAtSwap(Index);
			continue;
		}

		UCustomGravityComponent* GravityComponent = ResolveGravityComponent(Character);
		if (!GravityComponent)
		{
			continue;
		}

		if (bRadialSphereTakesPriority)
		{
			if (AActor* RadialField = FindOverlappingRadialField(Character))
			{
				const FVector RadialDirection =
					(RadialField->GetActorLocation() - Character->GetActorLocation())
					.GetSafeNormal();
				if (!RadialDirection.IsNearlyZero())
				{
					GravityComponent->SetGravityDirection(RadialDirection);
				}
				continue;
			}
		}

		bool bSurfaceFound = false;
		FHitResult SurfaceHit;
		const FVector NewGravity =
			USurfaceGravityBlueprintLibrary::FindNearestSurfaceGravityDirection(
				this,
				Character,
				this,
				bSurfaceFound,
				SurfaceHit,
				TraceDistance,
				ProbeRadius,
				SurfaceSwitchBias,
				DirectionInterpSpeed,
				TraceChannel,
				bDrawDebug);

		if (bSurfaceFound)
		{
			GravityComponent->SetGravityDirection(NewGravity);
		}
	}
}

void ASurfaceGravityFieldVolume::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	for (const TWeakObjectPtr<ACharacter>& CharacterPtr : CharactersInside)
	{
		if (ACharacter* Character = CharacterPtr.Get())
		{
			RemoveCharacter(Character, false);
		}
	}
	CharactersInside.Empty();

	Super::EndPlay(EndPlayReason);
}

void ASurfaceGravityFieldVolume::HandleBeginOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (!Character || (bOnlyAffectPlayers && !Character->IsPlayerControlled()))
	{
		return;
	}

	if (!CharactersInside.Contains(Character))
	{
		CharactersInside.Add(Character);
	}

	if (UCustomGravityComponent* GravityComponent = ResolveGravityComponent(Character))
	{
		GravityComponent->AddTickPrerequisiteActor(this);
		if (UCharacterMovementComponent* Movement = Character->GetCharacterMovement())
		{
			Movement->AddTickPrerequisiteComponent(GravityComponent);
		}
	}
}

void ASurfaceGravityFieldVolume::HandleEndOverlap(
	UPrimitiveComponent* OverlappedComponent,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComponent,
	int32 OtherBodyIndex)
{
	if (ACharacter* Character = Cast<ACharacter>(OtherActor))
	{
		RemoveCharacter(Character, true);
	}
}

UCustomGravityComponent* ASurfaceGravityFieldVolume::ResolveGravityComponent(
	ACharacter* Character)
{
	if (!Character)
	{
		return nullptr;
	}

	if (UCustomGravityComponent* Existing =
		Character->FindComponentByClass<UCustomGravityComponent>())
	{
		return Existing;
	}

	UCustomGravityComponent* Created = NewObject<UCustomGravityComponent>(
		Character,
		UCustomGravityComponent::StaticClass(),
		TEXT("RuntimeSurfaceGravity"));
	if (!Created)
	{
		return nullptr;
	}

	Created->bApplyInitialGravityOnBeginPlay = false;
	Character->AddInstanceComponent(Created);
	Created->RegisterComponent();
	return Created;
}

AActor* ASurfaceGravityFieldVolume::FindOverlappingRadialField(
	ACharacter* Character) const
{
	if (!Character)
	{
		return nullptr;
	}

	TArray<AActor*> OverlappingActors;
	Character->GetOverlappingActors(OverlappingActors);
	for (AActor* Actor : OverlappingActors)
	{
		if (!Actor || Actor == this)
		{
			continue;
		}

		const FString ClassName = Actor->GetClass()->GetName();
		if (ClassName.Contains(TEXT("GravityFeild_Sphere")) ||
			ClassName.Contains(TEXT("GravityField_Sphere")))
		{
			return Actor;
		}
	}

	return nullptr;
}

void ASurfaceGravityFieldVolume::RemoveCharacter(
	ACharacter* Character,
	bool bApplyExitGravity)
{
	if (!Character)
	{
		return;
	}

	CharactersInside.Remove(Character);
	if (UCustomGravityComponent* GravityComponent =
		Character->FindComponentByClass<UCustomGravityComponent>())
	{
		GravityComponent->RemoveTickPrerequisiteActor(this);
		if (bApplyExitGravity && bResetGravityOnExit &&
			!FindOverlappingRadialField(Character))
		{
			GravityComponent->SetGravityDirection(ExitGravityDirection);
		}
	}
}
