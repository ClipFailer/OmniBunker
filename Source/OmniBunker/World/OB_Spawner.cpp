// Copyright (c) 2026 OmniBunker Team. All rights reserved.


#include "OB_Spawner.h"
#include "Components/BoxComponent.h"
#include "../Interaction/OB_InteractableActor.h"
#include "Kismet/KismetMathLibrary.h"

AOB_Spawner::AOB_Spawner()
{
	// PrimaryActorTick.bCanEverTick = true;

	SpawnZone = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnZone"));
	RootComponent = SpawnZone;
}

void AOB_Spawner::SpawnItem() {
	if (PossibleItems.IsEmpty()) {
        UE_LOG(LogTemp, Warning, TEXT("Spawner %s: Список предметов пуст!"), *GetName());
        return;
    }

	const int32 ItemsToSpawnCount = FMath::RandRange(MinSpawnCount, MaxSpawnCount);
	for (int32 i = 0; i < ItemsToSpawnCount; ++i) {
		TSubclassOf<AOB_InteractableActor> ItemClass = GetRandomItemClass();
		if (!IsValid(ItemClass)) continue;

		FVector SpawnLocation = GetRandomPointInZone();
		FRotator SpawnRotation = FRotator(
			0.f,
			FMath::FRandRange(0.f, 360.f),
			0.f
		);

		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

		GetWorld()->SpawnActor<AOB_InteractableActor>(
			ItemClass,
			SpawnLocation,
			SpawnRotation,
			SpawnParams
		);
	}
}

void AOB_Spawner::BeginPlay()
{
	Super::BeginPlay();
	
	if (bSpawnOnBeginPlay) {
        SpawnItem();
    }
}

TSubclassOf<AOB_InteractableActor> AOB_Spawner::GetRandomItemClass() const {
	if (PossibleItems.IsEmpty()) return nullptr;

	float TotalWeight = 0.f;
	for (const auto& ItemClass : PossibleItems) {
		if (!IsValid(ItemClass)) continue;

		const AOB_InteractableActor* DefaultItem = ItemClass->GetDefaultObject<AOB_InteractableActor>();
		if (DefaultItem) {
			TotalWeight += DefaultItem->GetSpawnWeight();
		}
	}	

	if (TotalWeight <= 0.f) return nullptr;

	float RandomWeight = FMath::FRandRange(0.f, TotalWeight);
	for (const auto& ItemClass : PossibleItems) {
		if (!ItemClass) continue;

        const AOB_InteractableActor* DefaultItem = ItemClass->GetDefaultObject<AOB_InteractableActor>();
        if (!DefaultItem) continue;

		const float ItemWeight = DefaultItem->GetSpawnWeight();

		if (RandomWeight <= ItemWeight) {
			return ItemClass;
		}

		RandomWeight -= ItemWeight;
	}

	return PossibleItems[0];
}

FVector AOB_Spawner::GetRandomPointInZone() const {
	FVector Origin = SpawnZone->GetComponentLocation();
	FVector BoxExtent = SpawnZone->GetScaledBoxExtent();

	return UKismetMathLibrary::RandomPointInBoundingBox(Origin, BoxExtent);
}