// Copyright (c) 2026 OmniBunker Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CharacteristicMenuWidget.generated.h"

class UCharacteristicComponent;
class UCharacteristicWidget;
class UOB_CharacterCharacteristic;
enum class EOB_CharacteristicType : uint8;
class UVerticalBox;

/**
 * 
 */
UCLASS()
class OMNIBUNKER_API UCharacteristicMenuWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

	void Init(UCharacteristicComponent* CharacteristicComponent);

	UFUNCTION()
	void UpdateWidget(
		const EOB_CharacteristicType Type, 
		UOB_CharacterCharacteristic* Characteristic
	);

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UI")
	TSubclassOf<UCharacteristicWidget> WidgetClass;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere)
	TMap<EOB_CharacteristicType, UCharacteristicWidget*> Widgets;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UVerticalBox* WidgetsBox;
};
