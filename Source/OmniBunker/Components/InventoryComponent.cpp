// Copyright (c) 2026 OmniBunker Team. All rights reserved.


#include "InventoryComponent.h"
#include "../Data/OB_InventoryItemData.h"

UInventoryComponent::UInventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	InventorySlots.SetNum(InventorySize);
}

bool UInventoryComponent::AddItem(UOB_InventoryItemData* InItemData, const int32 Quantity) {
	if (!InItemData || Quantity <= 0) return false;

	int32 LeftToAdd = Quantity;

	// Проверяем стакается ли предмет.
	if (InItemData->bIsStackable) {
		// Проверяем есть ли такой же объект для объеденения стака
		for (int32 i = 0; i < InventorySize; ++i) {
			if (LeftToAdd <= 0) break;

			if (InventorySlots[i].ItemData == InItemData && InventorySlots[i].Quantity < InItemData->MaxStackSize) {
				int32 FreeSpaceInSlot = InItemData->MaxStackSize - InventorySlots[i].Quantity;
				int32 AmountToAdd = FMath::Min(LeftToAdd, FreeSpaceInSlot);

				InventorySlots[i].Quantity += AmountToAdd;
				LeftToAdd -= AmountToAdd;

				OnInventorySlotUpdated.Broadcast(i, InventorySlots[i]);
			}
		}
	}

	while (LeftToAdd > 0) {
		int32 EmptySlotIndex = FindEmptySlot();
		if (EmptySlotIndex == INDEX_NONE) return false;

		int32 AmountToAdd = FMath::Min(LeftToAdd, InItemData->MaxStackSize);

		InventorySlots[EmptySlotIndex] = FOB_InventorySlot(InItemData, AmountToAdd);
		LeftToAdd -= AmountToAdd;

		OnInventorySlotUpdated.Broadcast(EmptySlotIndex, InventorySlots[EmptySlotIndex]);
	}

	return true;
}

bool UInventoryComponent::RemoveItemFromSlot(const int32 SlotIndex, const int32 Quantity) {
	if (!InventorySlots.IsValidIndex(SlotIndex) || InventorySlots[SlotIndex].IsEmpty()) return false;

	if (InventorySlots[SlotIndex].Quantity <= Quantity) {
		InventorySlots[SlotIndex].Clear();
	} 
	else {
		InventorySlots[SlotIndex].Quantity -= Quantity;
	}

	OnInventorySlotUpdated.Broadcast(SlotIndex, InventorySlots[SlotIndex]);
	return true;
}

bool UInventoryComponent::UseItemAtSlot(const int32 SlotIndex) {
	return false;
}


void UInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
}

int32 UInventoryComponent::FindEmptySlot() const {
	for (int32 i = 0; i < InventorySize; ++i) {
		if (InventorySlots[i].IsEmpty()) return i;
	}

	return INDEX_NONE;
}

int32 UInventoryComponent::FindStackableSlot(UOB_InventoryItemData* InItemData) {
	for (int32 i = 0; i < InventorySize; ++i) {
		if (InItemData == InventorySlots[i].ItemData && 
			InventorySlots[i].Quantity < InItemData->MaxStackSize) {
				return i;
		}
	}

	return INDEX_NONE;
}

