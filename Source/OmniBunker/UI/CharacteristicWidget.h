// Copyright (c) 2026 OmniBunker Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacteristicWidget.generated.h"

class UTextBlock;
class UOB_CharacterCharacteristic;

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class OMNIBUNKER_API UCharacteristicWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	void SetWidget(UOB_CharacterCharacteristic* Characteristic);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void SetIsActive(const bool IsActive);
	virtual void SetIsActive_Implementation(const bool IsActive);

protected:

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* Name;

	// x

	bool bIsActive = false;
	
};
