// Copyright (c) 2026 OmniBunker Team. All rights reserved.


#include "CharacteristicComponent.h"
#include "../Characters/OB_BaseCharacter.h"
#include "../Data/OB_CharacteristicsPool.h"

// Sets default values for this component's properties
UCharacteristicComponent::UCharacteristicComponent()
{
	
}

UOB_CharacterCharacteristic* UCharacteristicComponent::GetCharacteristic(
	const EOB_CharacteristicType CharacteristicType
) {
	UOB_CharacterCharacteristic** FoundedChar = Characteristics.FindByPredicate(
		[CharacteristicType] (const UOB_CharacterCharacteristic* Characteristic) {
			return Characteristic && Characteristic->GetType() == CharacteristicType;
		}
	);

	return FoundedChar ? *FoundedChar : nullptr;
}

void UCharacteristicComponent::ApplyCharacteristicEffect(
	const EOB_CharacteristicType CharacteristicType
) {
	UOB_CharacterCharacteristic* FoundedChar = GetCharacteristic(CharacteristicType);
	if (!FoundedChar) return;

	if (!IsValid(CachedCharacterOwner)) return;
	FoundedChar->Affect(CachedCharacterOwner);
}

void UCharacteristicComponent::GenerateRandomCharacteristics() {
	Characteristics.Empty();
		
	for (const auto& Pool : CharacteristicsPool) {
		if (!IsValid(Pool)) {
            UE_LOG(
				LogTemp, 
				Warning,
				TEXT("CharacteristicsPool contains an invalid or null Pool entry!")
			);
            continue; 
        }

		TSubclassOf<UOB_CharacterCharacteristic> CharClass = Pool->GetRandomCharacteristic();
		if (!IsValid(CharClass)) {
			UE_LOG(LogTemp, Warning, TEXT("Characteristic Class is null!"));
			continue;
		}

		UOB_CharacterCharacteristic* Char = NewObject<UOB_CharacterCharacteristic>(this, CharClass);
		if (IsValid(Char)) {
			UE_LOG(
				LogTemp, 
				Warning, 
				TEXT("Characteristic: %s has loaded."), 
				*Char->GetDisplayName().ToString()
			);
			Characteristics.Add(Char);
			OnCharacteristicUpdated.Broadcast(Char->GetType(), Char);
		}
	}
}

// Called when the game starts
void UCharacteristicComponent::BeginPlay()
{
	Super::BeginPlay();

	CachedCharacterOwner = Cast<AOB_BaseCharacter>(GetOwner());
	
	// GenerateRandomCharacteristics();
}
