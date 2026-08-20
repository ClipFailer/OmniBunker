/// @file OB_InteractableActor.h
/// @author ClipFail (rogroty@gmail.com)
/// @brief Интерактивный эктор
/// @version 0.1
/// @date 2026-08-19
/// @copyright Copyright (c) 2026 OmniBunker Team. All rights reserved.

// Copyright (c) 2026 OmniBunker Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Interfaces/Interactable.h"
#include "OB_InteractableActor.generated.h"

#define ECC_InteractionObject ECC_GameTraceChannel1
#define ECC_InteractionTrace  ECC_GameTraceChannel2

class UWidgetComponent;
class UInteractionHintWidget;
class UOB_Condition;

/// @brief Класс интерактивного эктора
/// Предназначен для интерактивных объектов, с которыми игрок может взаимодействовать. 
UCLASS()
class OMNIBUNKER_API AOB_InteractableActor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	AOB_InteractableActor();

	/// @brief Реализация показа виджета взаимодействия.
	virtual void ShowInteractionHint_Implementation() override;
	/// @brief Реализация скрытия виджета взаимодействия.
    virtual void HideInteractionHint_Implementation() override;

	/// @brief C++ Реализация @ref IInteractable::CanInteract
	bool CanInteract_Implementation(AActor* Interactor) const;

	/// @brief Условия для успешного взаимодействия
	UPROPERTY(EditAnywhere, Instanced, Category = "Interaction|Conditions")
    TArray<TObjectPtr<UOB_Condition>> InteractionConditions;


	/// @brief Возвращает вес (логический) вес эктора
	/// Необходим для случайного выбора эктора для спауна. 
	/// @see AOB_Spawner::GetRandomItemClass
	/// @return @ref SpawnWeight "Логический вес" эктора
	float GetSpawnWeight() const { return SpawnWeight; };

	/// @brief Отключает возможность взаимодействия с эктором.
	UFUNCTION(BlueprintCallable, Category="Interaction")
	void DisableInteraction();

	/// @brief Проигрывает анимацию нажатия для виджета взаимодействия
	virtual void PlayWidgetClickAnim_Implementation() override;

protected:
	virtual void BeginPlay() override;

	/// @brief С++ реализация @ref IInteractable::Interact
	/// @param Interactor Персонаж, который совершил взаимодействие с эктором.
	virtual void Interact_Implementation(ACharacter* Interactor) override;

	/// @brief Реализация взаимодействия - вызвается при взаимодействии с эктором.
	///Виртуальный метод, который может быть переопределен в дочерних классах для реализации взаимодействия с эктором.
	/// @param Interactor Персонаж, который совершил взаимодействие с эктором.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="Interaction")
	void OnInteract(ACharacter* Interactor);

	/// @brief С++ реализация @ref AOB_InteractableActor::OnInteract
	/// @param Interactor Персонаж, который совершил взаимодействие с эктором.
	virtual void OnInteract_Implementation(ACharacter* Interactor);

	/// @brief Реализация взаимодействия - Сервер (Reliable)
	/// Метод вызывается если эктор реплицируется.
	/// @param Interactor Персонаж, который совершил взаимодействие с эктором.
	// UFUNCTION(Server, Reliable)
	// void Server_Interact_Reliable(ACharacter* Interactor);

	/// @brief Реализация взаимодействия - Сервер (Unreliable)
	/// Метод вызывается если эктор реплицируется.
	/// @param Interactor Персонаж, который совершил взаимодействие с эктором.
	// UFUNCTION(Server, Unreliable)
	// void Server_Interact_Unreliable(ACharacter* Interactor);

	/// @brief Метод, решаюший будет ли использоваться вариант RPC метода с Reliable или Unreliable
	/// Метод можно переопределять в дочерних классах, по умолчанию он возвращает true.
	/// @return true - Вызовется метод @ref AOB_InteractableActor::Server_Interact_Reliable | false - Вызовется метод @ref AOB_InteractableActor::Server_Interact_Unreliable
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category="RPC")
	bool ShouldUseReliableRPC();

	/// @brief C++ Реализация метода @ref AOB_InteractableActor::ShouldUseReliableRPC
	/// @return true Вызовется метод @ref AOB_InteractableActor::Server_Interact_Reliable
	/// @return false Вызовется метод @ref AOB_InteractableActor::Server_Interact_Unreliable
	virtual bool ShouldUseReliableRPC_Implementation() { return true; }

	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Mesh")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UWidgetComponent* InteractionWidgetComp;

	/// @brief Класс для отображения виджета взаимодействия
	/// По умолчанию используется @ref UInteractionHint (WBP_InteractionHint)
	UPROPERTY(EditDefaultsOnly, Category = "Interaction|UI")
	TSubclassOf<UInteractionHintWidget> InteractionWidgetClass;

	/// @brief Определяет, можно ли взаимодействовать с эктором
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction")
	bool bCanInteract = true;

	/// @brief Симиулирует ли физику эктор
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Physics")
	bool bSimulatePhysics = true;

	/// @brief Логический вес эктора
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawn Settings", meta = (ClampMin = "0.1"))
	float SpawnWeight = 1;

	/// @brief Физический вес эктора
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Phisics", meta = (ClampMin = "0.1"))
	float Weight;

	/// @brief Показывается ли виджет взаимодействия
	bool bCanHighlight = true;

private:
	UPROPERTY()
	UInteractionHintWidget* InteractionWidgetInstance = nullptr;
};
