// Copyright (c) 2026 OmniBunker Team. All rights reserved.


#include "CollectItemZone.h"
#include "Components/BoxComponent.h"
#include "../Interaction/OB_InventoryActor.h"
#include "../Data/OB_InventoryItemData.h"

ACollectItemZone::ACollectItemZone()
{
	OverlapZone = CreateDefaultSubobject<UBoxComponent>(TEXT("OverlapZone"));
	RootComponent = OverlapZone;
	OverlapZone->SetBoxExtent(FVector(100.f, 100.f, 25.f));
	OverlapZone->SetGenerateOverlapEvents(true);
	OverlapZone->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapZone->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapZone->SetCollisionResponseToChannel(ECC_InteractionObject, ECR_Overlap);

}

void ACollectItemZone::BeginPlay()
{
	Super::BeginPlay();

	if (IsValid(OverlapZone)) {
		OverlapZone->OnComponentBeginOverlap.AddDynamic(
			this, 
			&ThisClass::OnOverlapBegin
		);
		// OverlapZone->OnComponentEndOverlap.AddDynamic(
		// 	this, 
		// 	&ThisClass::OnOverlapEnd
		// );
	}
	
}

void ACollectItemZone::OnOverlapBegin(
	UPrimitiveComponent* OverlappedComponent, 
	AActor* OtherActor, 
    UPrimitiveComponent* OtherComp, 
	int32 OtherBodyIndex, 
    bool bFromSweep, 
	const FHitResult& SweepResult
) {
	if (AOB_InventoryActor* InventoryActor = Cast<AOB_InventoryActor>(OtherActor)) {
		UOB_InventoryItemData* ItemData = InventoryActor->GetItemData();
		const int32 Quantity = FMath::Max(InventoryActor->GetQuantity(), 1);

		// If Actor is AOB_InventoryActor, ItemData is correct and itemAmount > 0: 
		// add Actor to CollectedItems and destroy it.

		bool bSuccess = AddItem(ItemData, Quantity);
		if (bSuccess) { 
			OtherActor->Destroy();
		}
	}
	
}

// void ACollectItemZone::OnOverlapEnd(
// 	UPrimitiveComponent* OverlappedComponent, 
// 	AActor* OtherActor, 
// 	UPrimitiveComponent* 
// 	OtherComp, int32 OtherBodyIndex
// ) {
	
// }

bool ACollectItemZone::AddItem(UOB_InventoryItemData* ItemData, const int32 Amount) {
	if (!ItemData || Amount <= 0) return false;

	// Finding the existing item to increase total amount, else creating new ItemCollection.
	if (FItemCollection* ItemCollection = CollectedItems.FindByPredicate(
			[ItemData](const FItemCollection& ItemCollection) {
				return ItemCollection.ItemData == ItemData;
			}
		)
	) {
		ItemCollection->TotalAmount += Amount;

		UE_LOG(
			LogTemp, 
			Display, 
			TEXT("ACollectItemZone::AddItem: Item %s added. Total amount: %d"),
			*ItemData->ItemName.ToString(),
			ItemCollection->TotalAmount
		);

	} else {
		FItemCollection NewItemCollection;
		NewItemCollection.ItemData = ItemData;
		NewItemCollection.TotalAmount = Amount;

		CollectedItems.Add(NewItemCollection);

		UE_LOG(
			LogTemp, 
			Display, 
			TEXT("ACollectItemZone::AddItem: Item %s added. Total amount: %d"),
			*ItemData->ItemName.ToString(),
			NewItemCollection.TotalAmount
		);
	}

	return true;
}

	
// void ACollectItemZone::RemoveItem(UOB_InventoryItemData* ItemData, const int32 ItemAmount) {

// }