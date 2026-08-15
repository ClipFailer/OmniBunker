// Copyright (c) 2026 OmniBunker Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "../Data/OB_CharacterCharacteristic.h"
#include "CharacteristicComponent.generated.h"

class AOB_BaseCharacter;
class UOB_CharacteristicsPool;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(
	FOnCharacteristicUpdated, 
	EOB_CharacteristicType, Type, 
	UOB_CharacterCharacteristic*, UpdatedCharacteristic
);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OMNIBUNKER_API UCharacteristicComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UCharacteristicComponent();

	UOB_CharacterCharacteristic* GetCharacteristic(const EOB_CharacteristicType CharacteristicType);
	int32 GetCharacteristicsCount() const { return Characteristics.Num(); };
	const TArray<UOB_CharacterCharacteristic*>& GetCharacteristics() const { return Characteristics; }

	void ApplyCharacteristicEffect(const EOB_CharacteristicType CharacteristicType);

	void GenerateRandomCharacteristics();

	UPROPERTY(BlueprintAssignable)
	FOnCharacteristicUpdated OnCharacteristicUpdated;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TArray<UOB_CharacterCharacteristic*> Characteristics;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Data")
	TArray<UOB_CharacteristicsPool*> CharacteristicsPool;

	UPROPERTY()
    TObjectPtr<AOB_BaseCharacter> CachedCharacterOwner;
};
