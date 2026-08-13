// Copyright (c) 2026 OmniBunker Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "OB_InventoryItemData.generated.h"

class AOB_InventoryActor;

/**
 * 
 */
UCLASS()
class OMNIBUNKER_API UOB_InventoryItemData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:

    UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Item Logic")
    void UseItem(AActor* InventoryOwner);
    virtual void UseItem_Implementation(AActor* InventoryOwner) {}

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Info")
    FText ItemName;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Info", meta = (MultiLine = true))
    FText ItemDescription;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Info")
    UTexture2D* ItemThumbnail;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Info")
    bool bIsStackable = false;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Info", meta = (EditCondition = "bIsStackable"))
    int32 MaxStackSize = 1;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Item Info")
    TSubclassOf<AOB_InventoryActor> WorldPresentetionClass;
};
