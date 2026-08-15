// Copyright (c) 2026 OmniBunker Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OB_PlayerHud.generated.h"

class UOB_HotbarWidget;
class UCharacteristicMenuWidget;
class AOB_BaseCharacter;

/**
 * 
 */
UCLASS()
class OMNIBUNKER_API UOB_PlayerHud : public UUserWidget
{
	GENERATED_BODY()

public:

	void Init(AOB_BaseCharacter* Character);
	void SetHotbarVisibility(const bool bVisible);
	void ToggleCharMenu();


protected:

	void ShowCursor();
	void HideCursor();

	// Hotbar
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOB_HotbarWidget> HotbarWidget;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> HotbarAppearenceAnim;

	// Characteristic menu
	UFUNCTION()
	void OnCharMenuAppearenceEnded();

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UCharacteristicMenuWidget> CharacteristicMenuWidget;

	bool bIsCharMenuOpen = false;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> CharacteristicMenuWidgetAppearenceAnim;

	UPROPERTY()
	APlayerController* PlayerController;
};
