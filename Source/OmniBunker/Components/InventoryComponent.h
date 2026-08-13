// Copyright (c) 2026 OmniBunker Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryComponent.generated.h"

class UOB_InventoryItemData;
class AOB_InventoryActor;

USTRUCT(BlueprintType)
struct FOB_InventorySlot {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory")
	UOB_InventoryItemData* ItemData = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Inventory")
	int32 Quantity = 0;

	FOB_InventorySlot() {}
	FOB_InventorySlot(UOB_InventoryItemData* InItemData, const int32 InQuantity) 
		: ItemData(InItemData), Quantity(InQuantity) {}

	bool IsEmpty() const { return ItemData == nullptr || Quantity <= 0; }
	void Clear() { ItemData = nullptr; Quantity = 0; }

};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FOnInventorySlotUpdated, 
	int32, 
	SlotIndex, 
	const FOB_InventorySlot&, 
	NewSlotData
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnSelectedSlotChanged,
	int32,
	SlotIndex
);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OMNIBUNKER_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UInventoryComponent();

	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool AddItem(UOB_InventoryItemData* InItemData, const int32 Quantity = 1);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool RemoveItemFromSlot(const int32 SlotIndex, const int32 Quantity = 1);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	bool UseItemAtSlot(const int32 SlotIndex);

	UFUNCTION(BlueprintCallable, Category="Inventory")
	const TArray<FOB_InventorySlot>& GetInventorySlots() const { return InventorySlots; }

	void TakeToHand(int32 ItemIndex);
	void RemoveFromHand();
	void Drop();

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnInventorySlotUpdated OnInventorySlotUpdated;

	UPROPERTY(BlueprintAssignable, Category = "Inventory")
	FOnSelectedSlotChanged OnSelectedSlotChanged;

protected:
	virtual void BeginPlay() override;

	/**
	 * @brief Find a index of a empty inventory slot.
	 * 
	 * @return int32 - the empty slot's index.
	 */
	int32 FindEmptySlot() const;

	/**
	 * @brief Find appropriate slot's index which match with specified InItemData.
	 * 
	 * @param InItemData 
	 * @return int32 
	 */
	int32 FindStackableSlot(UOB_InventoryItemData* InItemData);

	UFUNCTION(BlueprintCallable)
	bool HasItem(UOB_InventoryItemData* ItemData, int32 QuantityRequired = 1) const;

	UFUNCTION(BlueprintCallable)
	int32 GetItemQuantity(UOB_InventoryItemData* ItemData) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Inventory")
    int32 InventorySize = 20;

private:

	UPROPERTY()
	TArray<FOB_InventorySlot> InventorySlots;

	UPROPERTY()
	AOB_InventoryActor* SelectedItem;

	int32 SelectedItemIndex = INDEX_NONE;
};
