// Copyright (c) 2026 OmniBunker Team. All rights reserved.


#include "CharacteristicMenuWidget.h"
#include "../Components/CharacteristicComponent.h"
#include "CharacteristicWidget.h"
#include "Components/VerticalBox.h"

void UCharacteristicMenuWidget::Init(UCharacteristicComponent* CharacteristicComponent) {
	if (!IsValid(CharacteristicComponent)) return;
	if (CharacteristicComponent->GetCharacteristicsCount() == 0) return;

	if (!IsValid(WidgetsBox)) return;
	
	Widgets.Empty();
	WidgetsBox->ClearChildren();

	CharacteristicComponent->OnCharacteristicUpdated.AddDynamic(
		this,
		&ThisClass::UpdateWidget
	);

	if (auto ProfessionWidget = CreateWidget<UCharacteristicWidget>(this, WidgetClass)) {
        Widgets.Add(EOB_CharacteristicType::Profession, ProfessionWidget);
        WidgetsBox->AddChildToVerticalBox(ProfessionWidget);
    }

    if (auto HealthStateWidget = CreateWidget<UCharacteristicWidget>(this, WidgetClass)) {
        Widgets.Add(EOB_CharacteristicType::HealthState, HealthStateWidget);
        WidgetsBox->AddChildToVerticalBox(HealthStateWidget);
    }

    if (auto HobbyWidget = CreateWidget<UCharacteristicWidget>(this, WidgetClass)) {
        Widgets.Add(EOB_CharacteristicType::Hobby, HobbyWidget);
        WidgetsBox->AddChildToVerticalBox(HobbyWidget);
    }

    if (auto PhobiaWidget = CreateWidget<UCharacteristicWidget>(this, WidgetClass)) {
        Widgets.Add(EOB_CharacteristicType::Phobia, PhobiaWidget);
        WidgetsBox->AddChildToVerticalBox(PhobiaWidget);
    }

    // 5. Если характеристики УЖЕ были сгенерированы к этому моменту, обновляем виджеты сразу
    for (auto& Pair : Widgets) {
        if (UOB_CharacterCharacteristic* ExistingChar = CharacteristicComponent->GetCharacteristic(Pair.Key)) {
            UpdateWidget(Pair.Key, ExistingChar);
        }
    }
}

void UCharacteristicMenuWidget::UpdateWidget(
	const EOB_CharacteristicType Type, 
	UOB_CharacterCharacteristic* Characteristic
) {
	if (UCharacteristicWidget** Widget = Widgets.Find(Type)) {
		(*Widget)->SetWidget(Characteristic);
	}
}