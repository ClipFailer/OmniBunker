// Copyright (c) 2026 OmniBunker Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CollectItemZone.generated.h"

class UBoxComponent;
class UOB_InventoryItemData;

#define ECC_InteractionObject ECC_GameTraceChannel1

USTRUCT(BlueprintType)
struct FItemCollection {
	GENERATED_BODY()

	UPROPERTY()
	UOB_InventoryItemData* ItemData;

	int32 TotalAmount;
};

UCLASS()
class OMNIBUNKER_API ACollectItemZone : public AActor
{
	GENERATED_BODY()
	
public:	
	ACollectItemZone();

	

protected:
	virtual void BeginPlay() override;

	// Calls when interactable actor begins overlap with OverlapZone.
	UFUNCTION()
    void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, 
                        bool bFromSweep, const FHitResult& SweepResult);

	// Calls when interactable actor ends overlap with OverlapZone.					
    // UFUNCTION()
    // void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
    //                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// Adds item to CollectedItems and returns true on success.
	bool AddItem(UOB_InventoryItemData* ItemData);

	// Removes item from CollectedItems.
	// void RemoveItem(UOB_InventoryItemData* ItemData);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Collect|Overlap")
	UBoxComponent* OverlapZone;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collect|Items")
	TArray<FItemCollection> CollectedItems;

};
