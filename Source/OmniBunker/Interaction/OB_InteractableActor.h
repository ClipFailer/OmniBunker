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

UCLASS()
class OMNIBUNKER_API AOB_InteractableActor : public AActor, public IInteractable
{
	GENERATED_BODY()
	
public:	
	AOB_InteractableActor();

	virtual void ShowInteractionHint_Implementation() override;
    virtual void HideInteractionHint_Implementation() override;

	UFUNCTION(BlueprintCallable, Category="Conditions")
	bool CanInteract(AActor* Interactor) const;

	UPROPERTY(EditAnywhere, Instanced, Category = "Interaction|Conditions")
    TArray<TObjectPtr<UOB_Condition>> InteractionConditions;

protected:
	virtual void BeginPlay() override;

	virtual void Interact_Implementation(ACharacter* Interactor) override;

	void PlayWidgetClickAnim();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Mesh")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UWidgetComponent* InteractionWidgetComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Interaction")
	bool bCanInteract = true;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Physics")
	bool bSimulatePhysics = true;

private:
	UPROPERTY()
	UInteractionHintWidget* InteractionWidgetInstance = nullptr;
};
