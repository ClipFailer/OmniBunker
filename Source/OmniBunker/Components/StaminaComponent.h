// Copyright (c) 2026 OmniBunker Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StaminaComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnStaminaIncreased,
	float,
	NewStamina
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnStaminaDecreased,
	float,
	NewStamina
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(
	FOnStaminaEnded
);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OMNIBUNKER_API UStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UStaminaComponent();

	void StartDecreaseStamina();
	void StartIncreaseStamina();
	void SpendStamina(const float Value);

	float GetCurrentStamina() const;
	float GetMinStaminaToSprint() const;
	float GetMinStaminaToJump() const;

	// === DELEGATES ===
	UPROPERTY(BlueprintAssignable)
	FOnStaminaDecreased OnStaminaDecreasedDelegate;
	UPROPERTY(BlueprintAssignable)
	FOnStaminaIncreased OnStaminaIncreasedDelegate;
	UPROPERTY(BlueprintAssignable)
	FOnStaminaEnded OnStaminaEndedDelegate;

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void IncreaseStamina();
	UFUNCTION()
	void DecreaseStamina();
	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Stamina")
	float MaxStamina = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Stamina")
	float CurrentStamina;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Stamina")
	float IncreaseStaminaValue = 0.6f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Stamina")
	float DecreaseStaminaValue = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Stamina")
	float MinStaminaToSprint = 10.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Stamina")
	float MinStaminaToJump = 15.f;
	
	// === TIMERS ===
	FTimerHandle IncreaseStaminaTimer;
	FTimerHandle DecreaseStaminaTimer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Stamina")
	float DecreaseStaminaDelay = 0.2f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Stamina")
	float IncreaseStaminaDelay = 0.2f;
	
};
