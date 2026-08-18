// Copyright (c) 2026 OmniBunker Team. All rights reserved.

#include "OB_BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"

#include "../Components/OB_HealthComponent.h"
#include "../Components/StaminaComponent.h"
#include "../Components/OB_InteractionComponent.h"
#include "../Components/InventoryComponent.h"
#include "../Components/CharacteristicComponent.h"
#include "../Interaction/OB_InventoryActor.h"

AOB_BaseCharacter::AOB_BaseCharacter()
{
    PrimaryActorTick.bCanEverTick = false;

    // bReplicates = true;

    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(GetCapsuleComponent());
    Camera->bUsePawnControlRotation = true;

    HealthComponent = CreateDefaultSubobject<UOB_HealthComponent>(TEXT("HealthComponent"));
    StaminaComponent = CreateDefaultSubobject<UStaminaComponent>(TEXT("StaminaComponent"));
    InteractionComponent = CreateDefaultSubobject<UOB_InteractionComponent>(TEXT("InteractionComponent"));
    InventoryComp = CreateDefaultSubobject<UInventoryComponent>(TEXT("InventoryComp"));
    CharacteristicComponent = CreateDefaultSubobject<UCharacteristicComponent>(TEXT("CharacteristicComponent"));
}

void AOB_BaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    UE_LOG(
        LogTemp, 
        Display, 
        TEXT("Character BeginPlay: %s, Controller: %s"), 
        *GetName(), 
        *GetNameSafe(GetController())
    );

    if (StaminaComponent) 
    {
        StaminaComponent->OnStaminaEndedDelegate.AddDynamic(this, &ThisClass::OnStaminaEnded);
    }
}

UInventoryComponent* AOB_BaseCharacter::GetInventoryComp_Implementation() const 
{
    return InventoryComp;
}

bool AOB_BaseCharacter::Pickup_Implementation(AOB_InventoryActor* InventoryActor) 
{
    if (!InventoryActor || !InventoryComp) return false;

    return InventoryComp->AddItem(
        InventoryActor->GetItemData(), 
        InventoryActor->GetQuantity()
    );
}

UOB_InteractionComponent* AOB_BaseCharacter::GetInteractionComp_Implementation() const 
{
    return InteractionComponent;
}

void AOB_BaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AOB_BaseCharacter::Move(const FInputActionValue& Value) 
{
    const FVector2D Axis = Value.Get<FVector2D>();

    if (Controller) 
    {
        const FRotator ControlRotator = FRotator(0.f, Controller->GetControlRotation().Yaw, 0.f);
        const FVector Forward = FRotationMatrix(ControlRotator).GetUnitAxis(EAxis::X);
        const FVector Right = FRotationMatrix(ControlRotator).GetUnitAxis(EAxis::Y);

        AddMovementInput(Forward, Axis.Y);
        AddMovementInput(Right, Axis.X);
    }
}

void AOB_BaseCharacter::Look(const FInputActionValue& Value) 
{
    const FVector2D Axis = Value.Get<FVector2D>();

    if (Controller) 
    {
        AddControllerYawInput(Axis.X);
        AddControllerPitchInput(-Axis.Y);
    }
}

void AOB_BaseCharacter::StartSprint(const FInputActionValue& Value) 
{
    if (!StaminaComponent || StaminaComponent->GetCurrentStamina() < StaminaComponent->GetMinStaminaToSprint())
        return;
    
    if (GetCharacterMovement())
        GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;

    StaminaComponent->StartDecreaseStamina();
}

void AOB_BaseCharacter::StopSprint(const FInputActionValue& Value) 
{
    if (GetCharacterMovement())
        GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

    if (StaminaComponent)
        StaminaComponent->StartIncreaseStamina();
}

void AOB_BaseCharacter::OnStaminaEnded() 
{
    if (GetCharacterMovement()) 
    {
        GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
    }
    
    if (StaminaComponent) 
    {
        StaminaComponent->StartIncreaseStamina();
    }
}

void AOB_BaseCharacter::DoJump(const FInputActionValue& Value) 
{
    if (!StaminaComponent || StaminaComponent->GetCurrentStamina() < StaminaComponent->GetMinStaminaToJump())
        return;

    Jump();

    StaminaComponent->SpendStamina(StaminaComponent->GetMinStaminaToJump());
}

void AOB_BaseCharacter::Interact(const FInputActionValue& Value) 
{
    if (InteractionComponent) 
    {
        InteractionComponent->Interact();
    }
}