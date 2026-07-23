// Copyright (c) 2026 OmniBunker Team. All rights reserved.


#include "OB_PlayerHud.h"
#include "OB_HotbarWidget.h"
#include "../Characters/OB_BaseCharacter.h"

void UOB_PlayerHud::Init(AOB_BaseCharacter* Character) {
	if (!Character) return;

	if (HotbarWidget)
		HotbarWidget->Init(Character->GetInventoryComp_Implementation());
}