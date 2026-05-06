// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/DRSCharacter.h"
#include "DRSPlayerCharacter.generated.h"

struct FInputActionValue;
struct FGameplayTag;

class UInputAction;
class UDRSInputConfig;
class UInputMappingContext;
class USpringArmComponent;
class UCameraComponent;

/**
 * Player-controlled DRS character with a third-person camera and Enhanced Input bindings.
 *
 * Adds camera components and translates Enhanced Input callbacks into movement, look, jump, and
 * gameplay-tag based ability input notifications for the ability system component.
 */
UCLASS()
class DUALRESOURCESYSTEM_API ADRSPlayerCharacter : public ADRSCharacter
{
	GENERATED_BODY()

public:
	/** Creates the player character camera boom and follow camera. */
	ADRSPlayerCharacter();

	/** Initializes Enhanced Input mappings and binds configured input actions. */
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	
protected:
	/** Third-person follow camera attached to the spring arm. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UCameraComponent> CameraComponent;

	/** Camera boom that follows controller rotation and positions the camera behind the character. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<USpringArmComponent> SpringArmComponent;
	
	/** Default Enhanced Input mapping context added for the owning local player. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TSoftObjectPtr<UInputMappingContext> DefaultInputMappingContext;
	
	/** Input configuration that maps ability input actions to gameplay tags. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UDRSInputConfig> DefaultInputConfig;
	
	/** Input action bound to ACharacter::Jump and ACharacter::StopJumping. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> JumpInputAction; 
	
	/** Input action used for character movement. Expects a FVector2D input value. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<UInputAction> MoveInputAction;
	
	/** Input action used for camera look input. Expects a FVector2D input value. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")	
	TObjectPtr<UInputAction> LookInputAction;

	
private:
	/** Adds the default mapping context to the local player and binds input actions. */
	void InitializePlayerInput();
	/** Binds ability input actions from the input config plus movement, look, and jump actions. */
	void BindInputActions();
	
	/** Handles movement input relative to the controller yaw. */
	UFUNCTION()
	void OnMoveInput(const FInputActionValue& InputValue);
	
	/** Handles look input by applying controller yaw and pitch input. */
	UFUNCTION()
	void OnLookInput(const FInputActionValue& InputValue);
	
	/** Forwards a triggered ability input tag to the ability system component. */
	UFUNCTION()
	void OnAbilityInputTriggered(FGameplayTag InputTag);
};
