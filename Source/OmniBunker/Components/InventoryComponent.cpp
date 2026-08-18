// Copyright (c) 2026 OmniBunker Team. All rights reserved.


#include "InventoryComponent.h"
#include "../Data/OB_InventoryItemData.h"
#include "../Interaction/OB_InventoryActor.h"
#include "GameFramework/Character.h"

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
		if (EmptySlotIndex == INDEX_NONE) break;

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

void UInventoryComponent::TakeToHand(int32 ItemIndex) {
	if (!InventorySlots.IsValidIndex(ItemIndex)) return;

	const FOB_InventorySlot& Slot = InventorySlots[ItemIndex];
	if (Slot.IsEmpty()) {
		RemoveFromHand();
		return;
	}

	RemoveFromHand();

	if (!Slot.ItemData->WorldPresentetionClass) return;

	AActor* OwnerActor = GetOwner();
    if (!OwnerActor) return;

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = OwnerActor;
	SpawnParams.Instigator = Cast<APawn>(OwnerActor);
	
	SelectedItem = OwnerActor->GetWorld()->SpawnActor<AOB_InventoryActor>(
        Slot.ItemData->WorldPresentetionClass,
        OwnerActor->GetActorTransform(),
        SpawnParams
    );

	if (SelectedItem) {
		SelectedItemIndex = ItemIndex;

		SelectedItem->SetActorEnableCollision(false);
		SelectedItem->DisableComponentsSimulatePhysics();

		if (ACharacter* CharacterOwner = Cast<ACharacter>(OwnerActor)) {
			SelectedItem->AttachToComponent(
				CharacterOwner->GetMesh(),
				FAttachmentTransformRules::SnapToTargetNotIncludingScale,
				TEXT("RightHandSocket")
			);
		}
	}
}

void UInventoryComponent::RemoveFromHand() {
	if (SelectedItem == nullptr) return; 

	SelectedItem->Destroy();
	SelectedItem = nullptr;
}

void UInventoryComponent::Drop() {
	if (!SelectedItem || SelectedItemIndex == INDEX_NONE) return;

    const int32 DroppedSlotIndex = SelectedItemIndex;

    SelectedItem->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
    SelectedItem->SetActorEnableCollision(true);

    TArray<UPrimitiveComponent*> PrimComponents;
    SelectedItem->GetComponents<UPrimitiveComponent>(PrimComponents);
    for (UPrimitiveComponent* PrimComp : PrimComponents) {
        if (PrimComp) {
            PrimComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
            PrimComp->SetSimulatePhysics(true);
            PrimComp->SetEnableGravity(true);
        }
    }

    if (AActor* OwnerActor = GetOwner()) {
        FVector Impulse = OwnerActor->GetActorForwardVector() * 250.f + FVector(0.f, 0.f, 80.f);
        if (UPrimitiveComponent* RootPrim = Cast<UPrimitiveComponent>(SelectedItem->GetRootComponent())) {
            RootPrim->AddImpulse(Impulse, NAME_None, true);
        }
    }

	UOB_InventoryItemData* ItemData = SelectedItem->GetItemData();
	if (ItemData) {
		if (ItemData->bDropAllStack) {
				int32 CurrentQuantity = InventorySlots[DroppedSlotIndex].Quantity;
				RemoveItemFromSlot(DroppedSlotIndex, CurrentQuantity);
		}
	} else {
		RemoveItemFromSlot(DroppedSlotIndex, 1);
	}

    SelectedItem = nullptr;
    SelectedItemIndex = INDEX_NONE;

    if (!InventorySlots[DroppedSlotIndex].IsEmpty()) {
        TakeToHand(DroppedSlotIndex);
    } 
    else {
        OnSelectedSlotChanged.Broadcast(INDEX_NONE);
    }
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

bool UInventoryComponent::HasItem(UOB_InventoryItemData* ItemData, int32 QuantityRequired) const {
	if (!ItemData || QuantityRequired <= 0) return false;

    return GetItemQuantity(ItemData) >= QuantityRequired;
}

int32 UInventoryComponent::GetItemQuantity(UOB_InventoryItemData* ItemData) const {
	if (!ItemData) return 0;

	int32 TotalCount = 0;

	for (const FOB_InventorySlot& Slot : InventorySlots) {
		if (Slot.ItemData == ItemData)
			TotalCount += Slot.Quantity;
	}

	return TotalCount;
}
