// Copyright (c) 2026 OmniBunker Team. All rights reserved.

#include "OB_BaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "../Components/OB_HealthComponent.h"
#include "../Components/StaminaComponent.h"
#include "../Components/OB_InteractionComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputTriggers.h"
// #include "Templates/Casts.h"

AOB_BaseCharacter::AOB_BaseCharacter()
{
	// PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetCapsuleComponent());
	Camera->bUsePawnControlRotation = true;

	HealthComponent = CreateDefaultSubobject<UOB_HealthComponent>(TEXT("HealthComponent"));
	StaminaComponent = CreateDefaultSubobject<UStaminaComponent>(TEXT("StaminaComponent"));
	InteractionComponent = CreateDefaultSubobject<UOB_InteractionComponent>(TEXT("InteractionComponent"));
}

void AOB_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	// Input
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller)) {
		if (ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer())
		if(UEnhancedInputLocalPlayerSubsystem* EnhancedSubsystem =
				ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer)) {
			if (DefaultMappingContext) {
				EnhancedSubsystem->AddMappingContext(DefaultMappingContext, 0);
			}
		}
	}

	// Stamina
	if (StaminaComponent) {
		StaminaComponent->OnStaminaEndedDelegate.AddDynamic(
			this, 
			&ThisClass::OnStaminaEnded
		);
	}
}

void AOB_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AOB_BaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedIC = CastChecked<UEnhancedInputComponent>(PlayerInputComponent)) {
		if (MoveIA) {
			EnhancedIC->BindAction(
				MoveIA, 
				ETriggerEvent::Triggered, 
				this, 
				&ThisClass::Move
			);
		}
		if (LookIA) {
			EnhancedIC->BindAction(
				LookIA, 
				ETriggerEvent::Triggered, 
				this, 
				&ThisClass::Look
			);
		}
		if (JumpIA) {
			EnhancedIC->BindAction(
				JumpIA, 
				ETriggerEvent::Started, 
				this, 
				&ThisClass::DoJump
			);
			EnhancedIC->BindAction(
				JumpIA, 
				ETriggerEvent::Completed, 
				this, 
				&ACharacter::StopJumping
			);
		}
		if (SprintIA) {
			EnhancedIC->BindAction(
				SprintIA, 
				ETriggerEvent::Started, 
				this, 
				&ThisClass::StartSprint
			);
			EnhancedIC->BindAction(
				SprintIA, 
				ETriggerEvent::Completed, 
				this, 
				&ThisClass::StopSprint
			);
		}
		if (InteractIA) {
			EnhancedIC->BindAction(
				InteractIA,
				ETriggerEvent::Started,
				this,
				&ThisClass::Interact
			);
		}
	}
}

void AOB_BaseCharacter::Move(const FInputActionValue& Value) {
	const FVector2D Axis = Value.Get<FVector2D>();

	if (Controller) {
		const FRotator ControlRotator = FRotator(
			0.f, 
			Controller->GetControlRotation().Yaw, 
			0.f
		);
		const FVector Forward = FRotationMatrix(ControlRotator).GetUnitAxis(EAxis::X);
		const FVector Right = FRotationMatrix(ControlRotator).GetUnitAxis(EAxis::Y);

		AddMovementInput(Forward, Axis.Y);
		AddMovementInput(Right, Axis.X);
	}
}

void AOB_BaseCharacter::Look(const FInputActionValue& Value) {
	const FVector2D Axis = Value.Get<FVector2D>();

	if (Controller) {
		AddControllerYawInput(Axis.X);
		AddControllerPitchInput(-Axis.Y);
	}
}

void AOB_BaseCharacter::StartSprint(const FInputActionValue& Value) {
	if (!StaminaComponent || 
			StaminaComponent->GetCurrentStamina() < StaminaComponent->GetMinStaminaToSprint())
		return;
	
	if (GetCharacterMovement())
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;

	StaminaComponent->StartDecreaseStamina();
}

void AOB_BaseCharacter::StopSprint(const FInputActionValue& Value) {
	if (GetCharacterMovement())
		GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;

	StaminaComponent->StartIncreaseStamina();
}

void AOB_BaseCharacter::OnStaminaEnded() {
	if (GetCharacterMovement()) {
        GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
    }
	
    if (StaminaComponent) {
        StaminaComponent->StartIncreaseStamina();
    }
}

void AOB_BaseCharacter::DoJump(const FInputActionValue& Value) {
	if (!StaminaComponent ||
			StaminaComponent->GetCurrentStamina() < StaminaComponent->GetMinStaminaToJump())
		return;

	Jump();

	StaminaComponent->SpendStamina(StaminaComponent->GetMinStaminaToJump());
}

void AOB_BaseCharacter::Interact(const FInputActionValue& Value) {
	if (!InteractionComponent) return;

	InteractionComponent->Interact();
}