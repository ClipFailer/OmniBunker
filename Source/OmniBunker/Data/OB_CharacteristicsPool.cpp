// Copyright (c) 2026 OmniBunker Team. All rights reserved.


#include "OB_CharacteristicsPool.h"

TSubclassOf<UOB_CharacterCharacteristic> UOB_CharacteristicsPool::GetRandomCharacteristic() const {
	if (Characteristics.Num() == 0) {
		UE_LOG(LogTemp, Warning, TEXT("Characteristic pool is empty!"));
		return nullptr;
	}

	const int32 RandomIndex = FMath::RandRange(0, Characteristics.Num() - 1);

	return Characteristics[RandomIndex];
}