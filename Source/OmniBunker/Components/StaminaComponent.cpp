// Copyright (c) 2026 OmniBunker Team. All rights reserved.


#include "StaminaComponent.h"

UStaminaComponent::UStaminaComponent()
{
	// PrimaryComponentTick.bCanEverTick = true;

}

void UStaminaComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentStamina = MaxStamina;
	
}

void UStaminaComponent::StartDecreaseStamina() {
	if (GetWorld()) {
		if (GetWorld()->GetTimerManager().IsTimerActive(IncreaseStaminaTimer))
			GetWorld()->GetTimerManager().ClearTimer(IncreaseStaminaTimer);

		GetWorld()->GetTimerManager().SetTimer(
			DecreaseStaminaTimer,
			this,
			&ThisClass::DecreaseStamina,
			DecreaseStaminaDelay,
			true
		);
	}
}

void UStaminaComponent::StartIncreaseStamina() {
	if (GetWorld()) {
		if (GetWorld()->GetTimerManager().IsTimerActive(DecreaseStaminaTimer))
			GetWorld()->GetTimerManager().ClearTimer(DecreaseStaminaTimer);

		GetWorld()->GetTimerManager().SetTimer(
			IncreaseStaminaTimer,
			this,
			&ThisClass::IncreaseStamina,
			IncreaseStaminaDelay,
			true
		);
	}
}

void UStaminaComponent::SpendStamina(const float Value) {
	if (Value <= 0) return;

	CurrentStamina = FMath::Max(CurrentStamina - Value, 0);

	OnStaminaDecreasedDelegate.Broadcast(CurrentStamina);

	UE_LOG(LogTemp, Warning, TEXT("Spended stamina: %f(-%f)"), CurrentStamina, Value);
}

float UStaminaComponent::GetCurrentStamina() const {
	return CurrentStamina;
}

float UStaminaComponent::GetMinStaminaToSprint() const {
	return MinStaminaToSprint;
}

float UStaminaComponent::GetMinStaminaToJump() const {
	return MinStaminaToJump;
}

void UStaminaComponent::IncreaseStamina() {
	CurrentStamina = FMath::Min(CurrentStamina + IncreaseStaminaValue, MaxStamina);

	OnStaminaIncreasedDelegate.Broadcast(CurrentStamina);

	if (CurrentStamina >= MaxStamina) {
		if (GetWorld()) {
			if (GetWorld()->GetTimerManager().IsTimerActive(IncreaseStaminaTimer))
				GetWorld()->GetTimerManager().ClearTimer(IncreaseStaminaTimer);
			}
		}

	UE_LOG(LogTemp, Warning, TEXT("Increased stamina: %f"), CurrentStamina);
}

void UStaminaComponent::DecreaseStamina() {
	SpendStamina(DecreaseStaminaValue);

	if (CurrentStamina <= 0) {
		OnStaminaEndedDelegate.Broadcast();

		if (GetWorld()) {
			if (GetWorld()->GetTimerManager().IsTimerActive(DecreaseStaminaTimer))
				GetWorld()->GetTimerManager().ClearTimer(DecreaseStaminaTimer);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Decreased stamina: %f"), CurrentStamina);

}