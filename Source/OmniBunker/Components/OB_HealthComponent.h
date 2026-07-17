// Copyright (c) 2026 OmniBunker Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OB_HealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnHeal,
	float,
	newHealth 
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(
	FOnDamaged,
	float,
	newHealth 
);

DECLARE_DYNAMIC_MULTICAST_DELEGATE(
	FOnDie
);


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OMNIBUNKER_API UOB_HealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

	UOB_HealthComponent();

	UFUNCTION(BlueprintCallable)
	float ApplyDamage(const float Damage);

	UFUNCTION(BlueprintCallable)
	float Heal(const float HP);

	UFUNCTION(BlueprintCallable)
	void Die();

	UPROPERTY(BlueprintAssignable, Category="Health")
	FOnHeal OnHealDelegate;
	UPROPERTY(BlueprintAssignable, Category="Health")
	FOnDamaged OnDamagedDelegate;
	UPROPERTY(BlueprintAssignable, Category="Health")
	FOnDie OnDieDelegate;

protected:

	virtual void BeginPlay() override;

	// == PROPERTIES ==

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Health")
	float MaxHealth = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Health")
	float CurrentHealth;
	
};
