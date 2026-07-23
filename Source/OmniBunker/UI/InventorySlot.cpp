// Copyright (c) 2026 OmniBunker Team. All rights reserved.


#include "InventorySlot.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "../Data/OB_InventoryItemData.h"

void UInventorySlot::UpdateSlot(UOB_InventoryItemData* InItemData, int32 InQuantity)
{
    CachedItemData = InItemData;
    CurrentQuantity = InQuantity;

    if (!CachedItemData || CurrentQuantity <= 0)
    {
        // Если слот пустой, гасим иконку и текст
        ItemIcon->SetVisibility(ESlateVisibility::Hidden);
        StackCountText->SetVisibility(ESlateVisibility::Hidden);
        return;
    }

    if (CachedItemData->ItemThumbnail)
    {
        ItemIcon->SetBrushFromTexture(CachedItemData->ItemThumbnail);
        ItemIcon->SetVisibility(ESlateVisibility::Visible);
    }

    if (CachedItemData->bIsStackable && CurrentQuantity > 1)
    {
        StackCountText->SetText(FText::AsNumber(CurrentQuantity));
        StackCountText->SetVisibility(ESlateVisibility::Visible);
    }
    else
    {
        StackCountText->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UInventorySlot::PlaySelectAnim(const bool bReverse)
{

    if (!SelectAnim) return;

    // Выбираем режим: Forward для обычного воспроизведения, Reverse для сброса
    const EUMGSequencePlayMode::Type PlayMode = bReverse ? 
        EUMGSequencePlayMode::Reverse : 
        EUMGSequencePlayMode::Forward;

    PlayAnimation(
        SelectAnim,
        0.f,
        1,
        PlayMode,
        1.f
    );

}