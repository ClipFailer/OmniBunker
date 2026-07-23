// Copyright (c) 2026 OmniBunker Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OB_HotbarWidget.generated.h"

class UInventoryComponent;
class UHorizontalBox;
class UInventorySlot;
struct FOB_InventorySlot;

/**
 * 
 */
UCLASS()
class OMNIBUNKER_API UOB_HotbarWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	// Initialiaze widget.
	void Init(UInventoryComponent* InInventoryComp);

	// Change selected hotabar slot.
	UFUNCTION()
	void SetSelectedSlot(int32 InSelectedSlotIndex);

	/**
	 * @brief Updates slot by index.
	 * 
	 */
	UFUNCTION()
	void UpdateSlot(
		int32 						SlotIndex, 
		const FOB_InventorySlot& 	SlotData
	);

protected:

	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* 				SlotHorizontalBox;

	UPROPERTY(EditAnywhere, Category="UI")
	TSubclassOf<UInventorySlot>		SlotWidgetClass;

	UPROPERTY()
	TArray<UInventorySlot*>			Slots;

	UInventoryComponent* 			InventoryComp;

private:

	int32 SelectedSlotIndex = INDEX_NONE;
};
