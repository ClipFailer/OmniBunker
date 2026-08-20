/**
 * @file OB_InteractableActor.h
 * @author ClipFail (rogroty@gmail.com)
 * @brief Интекрактивный эктор
 * @version 0.1
 * @date 2026-08-19
 * 
 * @copyright Copyright (c) 2026 OmniBunker Team. All rights reserved.
 * 
 */

// Copyright (c) 2026 OmniBunker Team. All rights reserved.


#include "OB_InteractableActor.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "../UI/InteractionHintWidget.h"
#include "../Interaction/OB_Condition.h"

AOB_InteractableActor::AOB_InteractableActor()
{
	PrimaryActorTick.bCanEverTick = false;

	bReplicates = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComponent->SetCollisionObjectType(ECC_InteractionObject);
	MeshComponent->SetCollisionResponseToChannel(ECC_InteractionTrace, ECR_Block);
	MeshComponent->SetGenerateOverlapEvents(true);
    MeshComponent->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);

	InteractionWidgetComp = CreateDefaultSubobject<UWidgetComponent>(
		TEXT("InteractionHint")
	);
	InteractionWidgetComp->SetupAttachment(RootComponent);
	

	static ConstructorHelpers::FClassFinder<UInteractionHintWidget> WidgetClassFinder(
		TEXT("/Game/_OmniBunker/UI/Interaction/WBP_InteractionHint")
	);
	if (WidgetClassFinder.Succeeded()) {
		InteractionWidgetClass = WidgetClassFinder.Class;
	} else {
		UE_LOG(
			LogTemp, 
			Error, 
			TEXT("AOB_InteractableActor::AOB_InteractableActor(): Failed to find default HintUI class")
		);
		InteractionWidgetClass = UInteractionHintWidget::StaticClass();
	}

	InteractionWidgetComp->SetWidgetClass(InteractionWidgetClass);
	InteractionWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);
	InteractionWidgetComp->SetDrawSize(FVector2D(80.f, 80.f));

}

void AOB_InteractableActor::ShowInteractionHint_Implementation() {
	
	
	if (!bCanHighlight) return;
	
	if (InteractionWidgetComp) {
		InteractionWidgetComp->SetVisibility(true);

		if (InteractionWidgetInstance) {
			InteractionWidgetInstance->PlayAppearAnim();
		}
	}
	
}

void AOB_InteractableActor::HideInteractionHint_Implementation() {
	if (!bCanHighlight) return;

	if (InteractionWidgetInstance)
		InteractionWidgetInstance->PlayAppearAnim(true);
}

bool AOB_InteractableActor::CanInteract_Implementation(AActor* Interactor) const {
	for (const UOB_Condition* Condition : InteractionConditions)
    {
        if (Condition && !Condition->Check(Interactor))
        {
            return false; 
        }
    }

    return true;
}

void AOB_InteractableActor::DisableInteraction() {
	bCanInteract = false;
	bCanHighlight = false;

	if (InteractionWidgetComp->IsWidgetVisible())
		InteractionWidgetComp->SetVisibility(false);
}

void AOB_InteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
	InteractionWidgetInstance = Cast<UInteractionHintWidget>	
								(InteractionWidgetComp->GetUserWidgetObject());
	
	if (InteractionWidgetInstance) 
		// InteractionWidgetInstance->SetRenderOpacity(0.f);	
	InteractionWidgetComp->SetVisibility(false);

	MeshComponent->SetSimulatePhysics(bSimulatePhysics);
}

void AOB_InteractableActor::Interact_Implementation(ACharacter* Interactor) {	
	if (!Interactor) return;
        
	// PlayWidgetClickAnim();

	OnInteract(Interactor);
	UE_LOG(
		LogTemp, 
		Display, 
		TEXT("%s interacted with by %s"), 
		*GetName(), 
		*Interactor->GetName()
	);
}

void AOB_InteractableActor::OnInteract_Implementation(ACharacter* Interactor) {
	
}

// void AOB_InteractableActor::Server_Interact_Reliable_Implementation(ACharacter* Interactor) {
//     OnInteract_Implementation(Interactor);
// }

// void AOB_InteractableActor::Server_Interact_Unreliable_Implementation(ACharacter* Interactor) {
//     OnInteract_Implementation(Interactor);
// }

void AOB_InteractableActor::PlayWidgetClickAnim_Implementation() {
	if (IsValid(InteractionWidgetInstance)) {
		InteractionWidgetInstance->PlayClickAnim();
	}
}