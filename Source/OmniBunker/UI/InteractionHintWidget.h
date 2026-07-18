// Copyright (c) 2026 OmniBunker Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InteractionHintWidget.generated.h"

class UWidgetAnimation;

/**
 * 
 */
UCLASS()
class OMNIBUNKER_API UInteractionHintWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void PlayAppearAnim(const bool bPlayReverse = false);
	void PlayClickAnim();

protected:

	UPROPERTY(Transient, meta = (BindWidgetAnim))
    UWidgetAnimation* AppearAnim;

    UPROPERTY(Transient, meta = (BindWidgetAnim))
    UWidgetAnimation* ClickAnim;
};
