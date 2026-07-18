// Copyright (c) 2026 OmniBunker Team. All rights reserved.


#include "OB_InteractionComponent.h"
#include "GameFramework/Character.h"
#include "Camera/CameraComponent.h"
#include "../Interfaces/Interactable.h"
#include "DrawDebugHelpers.h" 
#include "Components/BoxComponent.h"

UOB_InteractionComponent::UOB_InteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	InteractionZone = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionZone"));
	InteractionZone->SetBoxExtent(FVector(150.f, 150.f, 150.f));
	InteractionZone->SetCollisionProfileName(TEXT("Trigger"));
	InteractionZone->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	InteractionZone->SetCollisionResponseToChannel(
		ECC_InteractionObject, 
		ECR_Overlap
	);
}

void UOB_InteractionComponent::Interact() {
	if (!CurrentTargetActor) return;

	IInteractable::Execute_Interact(CurrentTargetActor, Cast<ACharacter>(GetOwner()));
}

void UOB_InteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	if (AActor* Owner = GetOwner()) {
		if (USceneComponent* Root = Owner->GetRootComponent()) {
			InteractionZone->AttachToComponent(
				Root, 
				FAttachmentTransformRules::KeepRelativeTransform
			);
		}
	}

	InteractionZone->OnComponentBeginOverlap.AddDynamic(
		this,
		&ThisClass::OnStartOverlapInteractionObject
	);
	InteractionZone->OnComponentEndOverlap.AddDynamic(
		this,
		&ThisClass::OnEndOverlapInteractionObject
	);

	SetComponentTickEnabled(false);
}

void UOB_InteractionComponent::DoInteractionTrace() {
	ACharacter* OwnerCharacter = Cast<ACharacter>(GetOwner());
	if (!OwnerCharacter) return;

	UCameraComponent* Camera = OwnerCharacter->FindComponentByClass<UCameraComponent>();
	if (!Camera) return;

	FVector TraceStart = Camera->GetComponentLocation();
	FVector TraceEnd = TraceStart + (Camera->GetForwardVector() * TraceDistance);

	FHitResult Hit;
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(OwnerCharacter);

	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse.SetAllChannels(ECR_Ignore);
	ResponseParams.CollisionResponse.SetResponse(ECC_InteractionObject, ECR_Block);


	bool bHit = GetWorld()->SweepSingleByChannel(
		Hit, 
		TraceStart, 
		TraceEnd, 
		FQuat::Identity, 
		ECC_InteractionTrace, 
		FCollisionShape::MakeSphere(TraceRadius), 
		QueryParams,
		ResponseParams
	);

	if (!bHit) {
		if (CurrentTargetActor)
			ResetTargetActor();

		return;
	}

	AActor* TargetActor = Hit.GetActor();
	if (!TargetActor || !TargetActor->Implements<UInteractable>()) {
        if (CurrentTargetActor)
            ResetTargetActor();
        return;
    }

	if (CurrentTargetActor) {
		if (TargetActor == CurrentTargetActor)
			return;
		ResetTargetActor();
	}

	SetTargetActor(TargetActor);
	UE_LOG(
		LogTemp, 
		Display, 
		TEXT("New Interaction Target: %s"), 
		*CurrentTargetActor->GetName()
	);
}

void UOB_InteractionComponent::SetTargetActor(AActor* TargetActor) {
	CurrentTargetActor = TargetActor;

	IInteractable::Execute_ShowInteractionHint(CurrentTargetActor);
}

void UOB_InteractionComponent::ResetTargetActor() {
	if (!IsValid(CurrentTargetActor)) return;
    
	IInteractable::Execute_HideInteractionHint(CurrentTargetActor);

	CurrentTargetActor = nullptr;
}

void UOB_InteractionComponent::OnStartOverlapInteractionObject(
	UPrimitiveComponent* 	OverlappedComponent, 
	AActor* 				OtherActor, 
	UPrimitiveComponent* 	OtherComp, 
	int32 					OtherBodyIndex, 
	bool 					bFromSweep, 
	const FHitResult& 		SweepResult
) {
	if (OtherActor && OtherActor->Implements<UInteractable>()) {
		InteractablesInRangeCount++;

		UE_LOG(
			LogTemp, 
			Display, 
			TEXT("New Interaction Target in zone: %d"), 
			InteractablesInRangeCount
		);

		if (InteractablesInRangeCount == 1) {
			if (GetWorld()) {
				GetWorld()->GetTimerManager().SetTimer(
					TraceTimer,
					this,
					&ThisClass::DoInteractionTrace,
					TraceTimerDelay,
					true
				);
			}
		}
	}
}

void UOB_InteractionComponent::OnEndOverlapInteractionObject(
	UPrimitiveComponent* 	OverlappedComponent, 
	AActor* 				OtherActor, 
	UPrimitiveComponent* 	OtherComp, 
	int32 					OtherBodyIndex
) {
	if (OtherActor && OtherActor->Implements<UInteractable>()) {
		InteractablesInRangeCount = FMath::Max(InteractablesInRangeCount - 1, 0);

		UE_LOG(
			LogTemp, 
			Display, 
			TEXT("Interaction Target in zone disappeared: %d"), 
			InteractablesInRangeCount
		);

		if (InteractablesInRangeCount <= 0) {
			if (GetWorld()) {
				GetWorld()->GetTimerManager().ClearTimer(TraceTimer);

				ResetTargetActor();
			}
		}
	}
}