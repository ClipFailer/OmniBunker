// Copyright (c) 2026 OmniBunker Team. All rights reserved.


#include "OB_InventoryActor.h"
#include "GameFramework/Character.h"
#include "../Interfaces/OB_CharacterInterface.h"
#include "../Data/OB_InventoryItemData.h"

void AOB_InventoryActor::OnInteract_Implementation(ACharacter* Interactor) {
	Super::OnInteract_Implementation(Interactor);

	if (!bCanInteract) return;

	if (!Interactor->Implements<UOB_CharacterInterface>()) return;
	if (!IOB_CharacterInterface::Execute_Pickup(Interactor, this)) return;

	UE_LOG(
		LogTemp, 
		Display, 
		TEXT("%s picked up to %s inventory"), 
		*GetName(), 
		*Interactor->GetName()
	);

	Destroy();
}