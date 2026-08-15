// Copyright (c) 2026 OmniBunker Team. All rights reserved.


#include "CharacteristicWidget.h"
#include "../Data/OB_CharacterCharacteristic.h"
#include "Components/TextBlock.h"

void UCharacteristicWidget::SetWidget(UOB_CharacterCharacteristic* Characteristic) {
	if (!IsValid(Characteristic)) return;

	Name->SetText(Characteristic->GetDisplayName());
}

void UCharacteristicWidget::SetIsActive_Implementation(const bool IsActive) {

}