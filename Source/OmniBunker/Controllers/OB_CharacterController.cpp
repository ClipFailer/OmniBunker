// Copyright (c) 2026 OmniBunker Team. All rights reserved.

#include "OB_CharacterController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

#include "../Characters/OB_BaseCharacter.h"
#include "../UI/OB_PlayerHud.h"
#include "../Components/InventoryComponent.h"

void AOB_CharacterController::BeginPlay() 
{
    Super::BeginPlay();

    if (!IsLocalController()) return;

    if (ULocalPlayer* LocalPlayer = GetLocalPlayer())
    {
        if (UEnhancedInputLocalPlayerSubsystem* EnhancedSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer)) 
        {
            if (DefaultMappingContext) 
            {
                EnhancedSubsystem->AddMappingContext(DefaultMappingContext, 0);
            }
        }
    }

    if (HudWidgetClass && IsLocalController()) 
    {
        PlayerHudWidget = CreateWidget<UOB_PlayerHud>(Cast<APlayerController>(this), HudWidgetClass);
        if (PlayerHudWidget) {
            PlayerHudWidget->AddToPlayerScreen();

            if (AOB_BaseCharacter* BaseChar = GetPawn<AOB_BaseCharacter>()) 
            {
                ControlledCharacter = BaseChar;
                PlayerHudWidget->Init(ControlledCharacter);
            }
        }
    }
}

void AOB_CharacterController::OnPossess(APawn* InPawn) 
{
    Super::OnPossess(InPawn);
    
    if (!InPawn) return;
    
    ControlledCharacter = Cast<AOB_BaseCharacter>(InPawn);

    if (PlayerHudWidget && ControlledCharacter){
            PlayerHudWidget->Init(ControlledCharacter);
    }
}

void AOB_CharacterController::SetupInputComponent()
{
    Super::SetupInputComponent();

    if (UEnhancedInputComponent* EnhancedIC = CastChecked<UEnhancedInputComponent>(InputComponent)) 
    {
        if (MoveIA) 
        {
            EnhancedIC->BindAction(MoveIA, ETriggerEvent::Triggered, this, &ThisClass::Move);
        }
        if (LookIA) 
        {
            EnhancedIC->BindAction(LookIA, ETriggerEvent::Triggered, this, &ThisClass::Look);
        }
        if (JumpIA) 
        {
            EnhancedIC->BindAction(JumpIA, ETriggerEvent::Started, this, &ThisClass::DoJump);
            EnhancedIC->BindAction(JumpIA, ETriggerEvent::Completed, this, &ThisClass::StopJump);
        }
        if (SprintIA) 
        {
            EnhancedIC->BindAction(SprintIA, ETriggerEvent::Started, this, &ThisClass::StartSprint);
            EnhancedIC->BindAction(SprintIA, ETriggerEvent::Completed, this, &ThisClass::StopSprint);
        }
        if (InteractIA) 
        {
            EnhancedIC->BindAction(InteractIA, ETriggerEvent::Started, this, &ThisClass::Interact);
        }
        if (SelectHotbarSlotIA) 
        {
            EnhancedIC->BindAction(SelectHotbarSlotIA, ETriggerEvent::Started, this, &ThisClass::SelectHotbarSlot);
        }
        if (DropSlotIA) 
        {
            EnhancedIC->BindAction(DropSlotIA, ETriggerEvent::Started, this, &ThisClass::DropSlot);
        }
        if (ToggleCharMenuIA) 
        {
            EnhancedIC->BindAction(ToggleCharMenuIA, ETriggerEvent::Started, this, &ThisClass::ToggleCharMenu);
        }
    }
}

void AOB_CharacterController::Move(const FInputActionValue& Value) 
{
    if (bBlockMovement) return;
    
    if (ControlledCharacter)
    {
        ControlledCharacter->Move(Value);
    }
}

void AOB_CharacterController::Look(const FInputActionValue& Value) 
{
    if (bBlockMovement) return;

    if (ControlledCharacter)
    {
        ControlledCharacter->Look(Value);
    }
}

void AOB_CharacterController::StartSprint(const FInputActionValue& Value) 
{
    if (bBlockMovement) return;

    if (ControlledCharacter)
    {
        ControlledCharacter->StartSprint(Value);
    }
}

void AOB_CharacterController::StopSprint(const FInputActionValue& Value) 
{
    if (ControlledCharacter)
    {
        ControlledCharacter->StopSprint(Value);
    }
}

void AOB_CharacterController::DoJump(const FInputActionValue& Value) 
{
    if (bBlockMovement) return;

    if (ControlledCharacter)
    {
        ControlledCharacter->DoJump(Value);
    }
}

void AOB_CharacterController::StopJump(const FInputActionValue& Value) 
{
    if (ControlledCharacter)
    {
        ControlledCharacter->StopJumping();
    }
}

void AOB_CharacterController::Interact(const FInputActionValue& Value) 
{
    if (bBlockMovement) return;

    if (ControlledCharacter)
    {
        ControlledCharacter->Interact(Value);
    }
}

void AOB_CharacterController::SelectHotbarSlot(const FInputActionValue& Value) {
    if (bBlockMovement) return;

    if (!ControlledCharacter) return;
    
    int32 SlotIndex = FMath::RoundToInt(Value.Get<float>());

    auto Inventory = IOB_CharacterInterface::Execute_GetInventoryComp(ControlledCharacter);
    if (Inventory)
        Inventory->OnSelectedSlotChanged.Broadcast(SlotIndex);
}

void AOB_CharacterController::DropSlot(const FInputActionValue& Value) {
    if (bBlockMovement) return;

    if (!ControlledCharacter) return;

    auto Inventory = 
            IOB_CharacterInterface::Execute_GetInventoryComp(ControlledCharacter);
    if (Inventory)
        Inventory->Drop();
}

void AOB_CharacterController::ToggleCharMenu(const FInputActionValue& Value) {
    if (!ControlledCharacter || !PlayerHudWidget) return;

   PlayerHudWidget->ToggleCharMenu();

   bBlockMovement = !bBlockMovement;
}