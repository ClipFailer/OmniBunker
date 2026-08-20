// Copyright (c) 2026 OmniBunker Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"


UINTERFACE(MinimalAPI)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};


/// @brief Интерфейс для экторов с которыми может взаимодействовать игрок
class OMNIBUNKER_API IInteractable
{
	GENERATED_BODY()
public:

	/// @brief Обёртка взаимодействия игрока
	/// Метод вызывается при взаимодействии игрока с эктором.
	/// Вызывает соответствующий метод в зависимости от репликации эктора.
	/// @param Interactor Персонаж, который совершил взаимодействие с эктором.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
	void Interact(ACharacter* Interactor);

	/// @brief Проверяет выполнены ли @ref InteractionConditions "Условия" для взаимодействия
	/// @param Interactor Персонаж игрока
	/// @return true все условия выполнены
	/// @return false хотя бы одно условие не выполнено
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
	bool CanInteract(AActor* Interactor) const;

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
	void ShowInteractionHint();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
	void PlayWidgetClickAnim();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
    void HideInteractionHint();
};
