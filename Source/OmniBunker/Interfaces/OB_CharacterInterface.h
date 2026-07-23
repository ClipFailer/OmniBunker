// Copyright (c) 2026 OmniBunker Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "OB_CharacterInterface.generated.h"

class UInventoryComponent;
class UOB_InteractionComponent;
class AOB_InventoryActor;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UOB_CharacterInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class OMNIBUNKER_API IOB_CharacterInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool Pickup(AOB_InventoryActor* InventoryActor);

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UInventoryComponent* GetInventoryComp() const;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	UOB_InteractionComponent* GetInteractionComp() const;
};
