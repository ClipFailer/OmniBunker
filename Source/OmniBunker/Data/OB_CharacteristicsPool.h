// Copyright (c) 2026 OmniBunker Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "OB_CharacteristicsPool.generated.h"

class UOB_CharacterCharacteristic;

/**
 * 
 */
UCLASS(BlueprintType)
class OMNIBUNKER_API UOB_CharacteristicsPool : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

	TSubclassOf<UOB_CharacterCharacteristic> GetRandomCharacteristic() const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<TSubclassOf<UOB_CharacterCharacteristic>> Characteristics;
};
