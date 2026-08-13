// Copyright (c) 2026 OmniBunker Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "OB_InteractableActor.h"
#include "OB_InventoryActor.generated.h"

class UOB_InventoryItemData;

/**
 * 
 */
UCLASS()
class OMNIBUNKER_API AOB_InventoryActor : public AOB_InteractableActor
{
	GENERATED_BODY()

public:

	UOB_InventoryItemData* GetItemData() const { return ItemData; };
	int32 GetQuantity() const { return Quantity; };
	void SetQuantity(const int32 NewQuantity) { Quantity = NewQuantity; };

protected:
	
	virtual void Interact_Implementation(ACharacter* Interactor) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Data")
	UOB_InventoryItemData* ItemData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Data")
	int32 Quantity = 1;

};
