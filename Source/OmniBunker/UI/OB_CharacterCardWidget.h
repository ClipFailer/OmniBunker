// Copyright (c) 2026 OmniBunker Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../Components/InventoryComponent.h"
#include "OB_CharacterCardWidget.generated.h"


/**
 * 
 */
UCLASS()
class OMNIBUNKER_API UOB_CharacterCardWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:

protected:
    // UFUNCTION()
    // void HandleSlotUpdated(int32 SlotIndex, const FOB_InventorySlot& SlotData);

    UPROPERTY(EditDefaultsOnly, Category = "Inventory|UI")
    TSubclassOf<UUserWidget> SlotWidgetClass;

    UPROPERTY(Transient, meta = (BindWidgetAnim))
    UWidgetAnimation* OpenMenuAnim;

    UPROPERTY(EditDefaultsOnly, Category = "Inventory|UI")
    int32 InventoryColumns = 3;

    UPROPERTY(EditDefaultsOnly, Category = "Inventory|UI")
    int32 InventoryRaws = 1;
};
