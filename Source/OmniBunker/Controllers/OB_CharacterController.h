// Copyright (c) 2026 OmniBunker Team. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OB_CharacterController.generated.h"

class UInputMappingContext;
class UInputAction;
class AOB_BaseCharacter;
class UOB_PlayerHud;
struct FInputActionValue;


/**
 * 
 */
UCLASS()
class OMNIBUNKER_API AOB_CharacterController : public APlayerController
{
	GENERATED_BODY()

public:


protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;

	TObjectPtr<AOB_BaseCharacter> ControlledCharacter;

	// === UI ===

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="UI")
	TSubclassOf<UOB_PlayerHud> HudWidgetClass;

	UPROPERTY()
	TObjectPtr<UOB_PlayerHud> PlayerHudWidget;

	// === INPUT ===

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void StartSprint(const FInputActionValue& Value);
	void StopSprint(const FInputActionValue& Value);
	void DoJump(const FInputActionValue& Value);
	void StopJump(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);
	void SelectHotbarSlot(const FInputActionValue& Value);
	void DropSlot(const FInputActionValue& Value);
	void ToggleCharMenu(const FInputActionValue& Value);

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputMappingContext* DefaultMappingContext;
	
	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* MoveIA;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* LookIA;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* JumpIA;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* SprintIA;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* InteractIA;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* SelectHotbarSlotIA;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* DropSlotIA;

	UPROPERTY(EditDefaultsOnly, Category="Input")
	UInputAction* ToggleCharMenuIA;

private:

	bool bBlockMovement = false;

};
