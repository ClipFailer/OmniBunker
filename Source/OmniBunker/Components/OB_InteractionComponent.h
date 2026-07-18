// Copyright (c) 2026 OmniBunker Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "OB_InteractionComponent.generated.h"

#define ECC_InteractionObject ECC_GameTraceChannel1
#define ECC_InteractionTrace  ECC_GameTraceChannel2

class UBoxComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class OMNIBUNKER_API UOB_InteractionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UOB_InteractionComponent();

	void Interact();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void DoInteractionTrace();
	void SetTargetActor(AActor* TargetActor);
	void ResetTargetActor();

	UFUNCTION()
	void OnStartOverlapInteractionObject(
		UPrimitiveComponent* 	OverlappedComponent, 
		AActor* 				OtherActor, 
		UPrimitiveComponent* 	OtherComp, 
		int32 					OtherBodyIndex, 
		bool 					bFromSweep, 
		const FHitResult& 		SweepResult
	);

	UFUNCTION()
    void OnEndOverlapInteractionObject(
		UPrimitiveComponent* 	OverlappedComponent, 
		AActor* 				OtherActor, 
		UPrimitiveComponent* 	OtherComp, 
		int32 					OtherBodyIndex
	);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Interaction")
	UBoxComponent* InteractionZone;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction")
	float TraceDistance = 250.f;	

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction")
	float TraceRadius = 25.f;	

	FTimerHandle TraceTimer;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Interaction")
	float TraceTimerDelay = 0.3;

private:
	UPROPERTY()
	AActor* CurrentTargetActor = nullptr;

	int32 InteractablesInRangeCount = 0;
};
