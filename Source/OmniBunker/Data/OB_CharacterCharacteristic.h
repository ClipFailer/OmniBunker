// Copyright (c) 2026 OmniBunker Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "OB_CharacterCharacteristic.generated.h"

class AOB_BaseCharacter;

UENUM(BlueprintType)
enum class EOB_CharacteristicType : uint8
{
    None        UMETA(DisplayName = "Нет"),
    Profession  UMETA(DisplayName = "Профессия"),
    Phobia      UMETA(DisplayName = "Фобия"),
    HealthState UMETA(DisplayName = "Состояние здоровья / Болезнь"),
    Hobby       UMETA(DisplayName = "Хобби / Навык")
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class OMNIBUNKER_API UOB_CharacterCharacteristic : public UObject
{
	GENERATED_BODY()
	
public:

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
    void Affect(AOB_BaseCharacter* Character);
    virtual void Affect_Implementation(AOB_BaseCharacter* Character);

    EOB_CharacteristicType GetType() const;
    FText GetDisplayName() const { return DisplayName; };
    FText GetDescription() const { return Description; };

protected:

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Data")
    EOB_CharacteristicType CharacteristicType;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    FText DisplayName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
    FText Description;

};
