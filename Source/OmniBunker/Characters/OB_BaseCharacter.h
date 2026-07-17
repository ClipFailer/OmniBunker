// Copyright (c) 2026 OmniBunker Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"
#include "OB_BaseCharacter.generated.h"

class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UOB_HealthComponent;
class UStaminaComponent;

UCLASS()
class OMNIBUNKER_API AOB_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AOB_BaseCharacter();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartSprint(const FInputActionValue& Value);
	void StopSprint(const FInputActionValue& Value);
	UFUNCTION()
	void OnStaminaEnded();
	void DoJump(const FInputActionValue& Value);

	// === COMPONENTS ===

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Camera")
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Health")
	UOB_HealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Stamina")
	UStaminaComponent* StaminaComponent;

	// === PROPERTIES ===

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement")
	float WalkSpeed = 600;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement")
	float SprintSpeed = 900;

	// === INPUT ===
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* MoveIA;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* LookIA;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* JumpIA;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* SprintIA;
};
