// Copyright (c) 2026 OmniBunker Team. All rights reserved.

#include "OB_HealthComponent.h"

float UOB_HealthComponent::ApplyDamage(const float Damage) {
	if (Damage <= 0)
		return CurrentHealth;

	CurrentHealth = FMath::Max(CurrentHealth - Damage, 0);

	OnDamagedDelegate.Broadcast(CurrentHealth);

	if (CurrentHealth <= 0)
		Die();

	UE_LOG(LogTemp, Warning, TEXT("Damaged: %f"), CurrentHealth);

	return CurrentHealth;
}

float UOB_HealthComponent::Heal(const float HP) {
	if (HP <= 0)
		return CurrentHealth;

	CurrentHealth = FMath::Min(CurrentHealth + HP, MaxHealth);

	OnHealDelegate.Broadcast(CurrentHealth);

	UE_LOG(LogTemp, Warning, TEXT("Heal: %f"), CurrentHealth);

	return CurrentHealth;
}

void UOB_HealthComponent::Die() {

	UE_LOG(LogTemp, Warning, TEXT("Died"));

	OnDieDelegate.Broadcast();
}

UOB_HealthComponent::UOB_HealthComponent()
{
	
}


// Called when the game starts
void UOB_HealthComponent::BeginPlay()
{
	Super::BeginPlay();

	CurrentHealth = MaxHealth;
}


