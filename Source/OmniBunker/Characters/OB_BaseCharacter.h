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

UCLASS()
class OMNIBUNKER_API AOB_BaseCharacter : public ACharacter, public IOB_CharacterInterface
{
    GENERATED_BODY()

public:
    AOB_BaseCharacter();

    virtual void Tick(float DeltaTime) override;

    virtual UInventoryComponent* GetInventoryComp_Implementation() const override;
    virtual bool Pickup_Implementation(AOB_InventoryActor* InventoryActor) override;
    virtual UOB_InteractionComponent* GetInteractionComp_Implementation() const override;

    UCharacteristicComponent* GetCharacteristicComp() const { return CharacteristicComponent; };

    // Публичные методы выполнения действий
    void Move(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
    void StartSprint(const FInputActionValue& Value);
    void StopSprint(const FInputActionValue& Value);
    void DoJump(const FInputActionValue& Value);
    void Interact(const FInputActionValue& Value);

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