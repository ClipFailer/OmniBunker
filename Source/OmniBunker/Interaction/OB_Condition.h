// Copyright (c) 2026 OmniBunker Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "OB_Condition.generated.h"

/**
 * 
 */
UCLASS(Abstract, Blueprintable, EditInlineNew, DefaultToInstanced)
class OMNIBUNKER_API UOB_Condition : public UObject
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Conditions")
	bool Check(AActor* Instigator) const;
	virtual bool Check_Implementation(AActor* Instigator) const;
	
};
