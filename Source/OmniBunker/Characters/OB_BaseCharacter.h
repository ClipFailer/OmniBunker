/// @file Класс игрока
/// @author Clipfail (rogroty@gmai.com)
/// @brief 
/// @version 0.1
/// @date 19-08-2026
/// 
/// @copyright Copyright (c) 2026 OmniBunker Team. All rights reserved.
/// 

// Copyright (c) 2026 OmniBunker Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "../Interfaces/OB_CharacterInterface.h"
#include "OB_BaseCharacter.generated.h"

class UCameraComponent;
class UOB_HealthComponent;
class UStaminaComponent;
class UOB_InteractionComponent;
class UInventoryComponent;
class UCharacteristicComponent;

/// @brief Класс игрока
UCLASS()
class OMNIBUNKER_API AOB_BaseCharacter : public ACharacter, public IOB_CharacterInterface
{
    GENERATED_BODY()

public:
    AOB_BaseCharacter();

    virtual void Tick(float DeltaTime) override;

    UFUNCTION(Server, Reliable)
    void Server_Interact(AActor* Target);

    /// @brief C++ Реализация @ref UOB_CharacterInterface::GetInventoryComp
    /// @return UInventoryComponent* конмпонент инвентаря игрока
    virtual UInventoryComponent* GetInventoryComp_Implementation() const override;

    /// @brief C++ Реализация @ref UOB_CharacterInterface::Pickup
    /// @param InventoryActor Эктор, который игрок хочет поднять
    /// @return true Эктор был добавлен в инвентрарь успешно.
    /// @return false Эктор не был добавлен в инвентрарь.
    virtual bool Pickup_Implementation(AOB_InventoryActor* InventoryActor) override;
    virtual UOB_InteractionComponent* GetInteractionComp_Implementation() const override;

    /// @brief C++ Реализация @ref UOB_CharacterInterface::GetInteractionComp
    /// @return UCharacteristicComponent* конмпонент взаимодействия игрока.
    UCharacteristicComponent* GetCharacteristicComp() const { return CharacteristicComponent; };

    /// @brief Выполняет движение игрока.
    /// @param Value Значение ввода.
    void Move(const FInputActionValue& Value);

    /// @brief Выполняет движение камеры игрока.
    /// @param Value Значение ввода.
    void Look(const FInputActionValue& Value);

    /// @brief Начинает бег игрока.
    /// @param Value Значение ввода.
    void StartSprint(const FInputActionValue& Value);

    /// @brief Завершает бег игрока.
    /// @param Value Значение ввода.
    void StopSprint(const FInputActionValue& Value);

    /// @brief Выполняет прыжок.
    /// @param Value Значение ввода.
    void DoJump(const FInputActionValue& Value);

    /// @brief Выполняет взаимодействие игрока с интерактивными объектами.
    /// @param Value Значение ввода.
    void Interact(const FInputActionValue& Value);

    /// @brief Вызывается при истощении стамины.
    UFUNCTION()
    void OnStaminaEnded();

protected:
    virtual void BeginPlay() override;

    // === COMPONENTS ===

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
    TObjectPtr<UCameraComponent> Camera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Health")
    TObjectPtr<UOB_HealthComponent> HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Stamina")
    TObjectPtr<UStaminaComponent> StaminaComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interaction")
    TObjectPtr<UOB_InteractionComponent> InteractionComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Inventory")
    TObjectPtr<UInventoryComponent> InventoryComp;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Inventory")
    TObjectPtr<UCharacteristicComponent> CharacteristicComponent;

    // === PROPERTIES ===

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement")
    float WalkSpeed = 600.f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement")
    float SprintSpeed = 900.f;
};