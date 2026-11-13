// Copyright (c) 2026 OmniBunker Team. All rights reserved.


#include "OB_PlayerHud.h"
#include "OB_HotbarWidget.h"
#include "CharacteristicMenuWidget.h"
#include "../Characters/OB_BaseCharacter.h"
#include "../Components/CharacteristicComponent.h"

void UOB_PlayerHud::Init(AOB_BaseCharacter* Character) {
	if (!Character) return;
	if (InitializedCharacter == Character) return;
	InitializedCharacter = Character;

	PlayerController = Cast<APlayerController>(Character->GetController());

	if (HotbarWidget)
		HotbarWidget->Init(Character->GetInventoryComp_Implementation());

	if (CharacteristicMenuWidget) {
		auto CharComp = Character->GetCharacteristicComp();
		if (IsValid(CharComp)) {
			CharComp->GenerateRandomCharacteristics();
			CharacteristicMenuWidget->Init(CharComp);
			CharacteristicMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
		}
	}
}

void UOB_PlayerHud::ToggleCharMenu() {
	if (!IsValid(CharacteristicMenuWidget)) 
		return;

	UE_LOG(LogTemp, Warning, TEXT("CharMenu visibility: %d"), bIsCharMenuOpen);

	if (bIsCharMenuOpen) {
		if (CharacteristicMenuWidgetAppearenceAnim) {
			FWidgetAnimationDynamicEvent OnCharMenuAnimEnded;
			OnCharMenuAnimEnded.BindDynamic(this, &ThisClass::OnCharMenuAppearenceEnded);

			BindToAnimationFinished(CharacteristicMenuWidgetAppearenceAnim, OnCharMenuAnimEnded);
			PlayAnimationReverse(CharacteristicMenuWidgetAppearenceAnim);
		} else {
			CharacteristicMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
		}

		HideCursor();

	} else {
		ShowCursor();

		CharacteristicMenuWidget->SetVisibility(ESlateVisibility::Visible);
		if (CharacteristicMenuWidgetAppearenceAnim) {
			PlayAnimation(CharacteristicMenuWidgetAppearenceAnim);
		}
	}

	bIsCharMenuOpen = !bIsCharMenuOpen;
}

void UOB_PlayerHud::OnCharMenuAppearenceEnded() {
	CharacteristicMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	UnbindAllFromAnimationFinished(CharacteristicMenuWidgetAppearenceAnim);
}

void UOB_PlayerHud::ShowCursor()
{
    if (PlayerController)
    {
        PlayerController->bShowMouseCursor = true;
        FInputModeGameAndUI InputMode;
        InputMode.SetWidgetToFocus(TakeWidget());
        InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
        PlayerController->SetInputMode(InputMode);
    }
}

void UOB_PlayerHud::HideCursor()
{
    if (PlayerController)
    {
        PlayerController->bShowMouseCursor = false;
        FInputModeGameOnly InputMode;
        PlayerController->SetInputMode(InputMode);
    }
}