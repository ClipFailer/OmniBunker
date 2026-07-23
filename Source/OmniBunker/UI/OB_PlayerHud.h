// Copyright (c) 2026 OmniBunker Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OB_PlayerHud.generated.h"

class UOB_HotbarWidget;
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

protected:

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UOB_HotbarWidget> HotbarWidget;

	UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> HotbarAppearenceAnim;
	
};
