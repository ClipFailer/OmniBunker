// Copyright (c) 2026 OmniBunker Team. All rights reserved.


#include "OB_InteractableActor.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/Character.h"
#include "../UI/InteractionHintWidget.h"

AOB_InteractableActor::AOB_InteractableActor()
{
	PrimaryActorTick.bCanEverTick = false;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComponent"));
	RootComponent = MeshComponent;
	MeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	MeshComponent->SetCollisionObjectType(ECC_InteractionObject);
	MeshComponent->SetCollisionResponseToChannel(ECC_InteractionTrace, ECR_Block);

	InteractionWidgetComp = CreateDefaultSubobject<UWidgetComponent>(
		TEXT("InteractionHint")
	);
	InteractionWidgetComp->SetupAttachment(RootComponent);
	InteractionWidgetComp->SetWidgetSpace(EWidgetSpace::Screen);

	
}

void AOB_InteractableActor::ShowInteractionHint_Implementation() {	
	if (!InteractionWidgetComp->IsWidgetVisible())
		InteractionWidgetComp->SetVisibility(true);
	
	if (InteractionWidgetInstance)
		InteractionWidgetInstance->PlayAppearAnim();
}

void AOB_InteractableActor::HideInteractionHint_Implementation() {

	if (InteractionWidgetInstance)
		InteractionWidgetInstance->PlayAppearAnim(true);
}

void AOB_InteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
	InteractionWidgetInstance = Cast<UInteractionHintWidget>	
								(InteractionWidgetComp->GetUserWidgetObject());
	
	// if (InteractionWidgetInstance) 
		// InteractionWidgetInstance->SetRenderOpacity(0.f);	
	InteractionWidgetComp->SetVisibility(false);

}

void AOB_InteractableActor::Interact_Implementation(ACharacter* Interactor) {
	if (!Interactor) return;
        
	PlayWidgetClickAnim();

	if (!bCanInteract) return;

	UE_LOG(
		LogTemp, 
		Display, 
		TEXT("%s interacted with by %s"), 
		*GetName(), 
		*Interactor->GetName()
	);
}

void AOB_InteractableActor::PlayWidgetClickAnim() {
	InteractionWidgetInstance->PlayClickAnim();
}