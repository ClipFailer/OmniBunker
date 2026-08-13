// Copyright (c) 2026 OmniBunker Team. All rights reserved.


#include "OB_HotbarWidget.h"
#include "Components/HorizontalBox.h"

#include "../Components/InventoryComponent.h"
#include "../UI/InventorySlot.h"

void UOB_HotbarWidget::Init(UInventoryComponent* InInventoryComp) {
	if (!InInventoryComp) return;
	if (!SlotWidgetClass) return;

	InventoryComp = InInventoryComp;

	InventoryComp->OnInventorySlotUpdated.RemoveDynamic(this, &ThisClass::UpdateSlot);
	InventoryComp->OnInventorySlotUpdated.AddDynamic(this, &ThisClass::UpdateSlot);
	InventoryComp->OnSelectedSlotChanged.RemoveDynamic(this, &ThisClass::SetSelectedSlot);
	InventoryComp->OnSelectedSlotChanged.AddDynamic(this, &ThisClass::SetSelectedSlot);

	SlotHorizontalBox->ClearChildren();
	Slots.Empty();

	const TArray<FOB_InventorySlot>& InventorySlots = InventoryComp->GetInventorySlots();
	for (int32 i = 0; i < InventorySlots.Num(); ++i) {
		UInventorySlot* NewWidget = CreateWidget<UInventorySlot>(
			this, 
			SlotWidgetClass
		);

		NewWidget->UpdateSlot(InventorySlots[i].ItemData, InventorySlots[i].Quantity);

		SlotHorizontalBox->AddChildToHorizontalBox(NewWidget);

		Slots.Add(NewWidget);
	}
}

void UOB_HotbarWidget::UpdateSlot(int32 SlotIndex, const FOB_InventorySlot& SlotData) {
	if (!Slots.IsValidIndex(SlotIndex)) return;

	Slots[SlotIndex]->UpdateSlot(SlotData.ItemData, SlotData.Quantity);
}

void UOB_HotbarWidget::SetSelectedSlot(int32 InSelectedSlotIndex) {
	if (!InventoryComp) return;

    int32 TargetIndex = (InSelectedSlotIndex > 0) ? (InSelectedSlotIndex - 1) : INDEX_NONE;

    if (TargetIndex != INDEX_NONE && TargetIndex == SelectedSlotIndex) {
        TargetIndex = INDEX_NONE;
		InventoryComp->RemoveFromHand();
    }

    if (Slots.IsValidIndex(SelectedSlotIndex)) {
        Slots[SelectedSlotIndex]->PlaySelectAnim(true); 
    }

    SelectedSlotIndex = TargetIndex;

    if (Slots.IsValidIndex(SelectedSlotIndex)) {
        Slots[SelectedSlotIndex]->PlaySelectAnim(false);
    }
	
	InventoryComp->TakeToHand(SelectedSlotIndex);

    UE_LOG(LogTemp, Warning, TEXT("Current Selected Slot: %d"), SelectedSlotIndex);
}
