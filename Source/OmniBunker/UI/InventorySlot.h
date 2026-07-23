// Copyright (c) 2026 OmniBunker Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "InventorySlot.generated.h"

class UImage;
class UTextBlock;
class UOB_InventoryItemData;

/**
 * 
 */
UCLASS()
class OMNIBUNKER_API UInventorySlot : public UUserWidget
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable, Category = "Inventory|UI")
    void UpdateSlot(UOB_InventoryItemData* InItemData, int32 InQuantity);

    UFUNCTION(BlueprintCallable, Category = "Inventory|UI")
    void PlaySelectAnim(const bool bReverse = false);

protected:
    UPROPERTY(meta = (BindWidget))
    UImage* ItemIcon;

    UPROPERTY(meta = (BindWidget))
    UTextBlock* StackCountText;

    UPROPERTY(Transient, meta = (BindWidgetAnim))
    UWidgetAnimation* SelectAnim;

    UPROPERTY(Transient, meta = (BindWidgetAnim))
    UWidgetAnimation* HoverAnim;

private:
    UPROPERTY()
    UOB_InventoryItemData* CachedItemData;

    int32 CurrentQuantity = 0;
	
};
