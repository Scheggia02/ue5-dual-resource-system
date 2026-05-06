// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/DRSPlayerCharacter.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Camera/CameraComponent.h"
#include "InputMappingContext.h"
#include "Components/DRSAbilitySystemComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Input/DRSGameplayTags.h"
#include "Input/DRSInputConfig.h"

ADRSPlayerCharacter::ADRSPlayerCharacter()
{
	// Create a camera boom (pulls in towards the player if there is a collision)
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
	SpringArmComponent->SetupAttachment(RootComponent);
	SpringArmComponent->TargetArmLength = 400.f; // The camera follows at this distance behind the character
	SpringArmComponent->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	CameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

void ADRSPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	InitializePlayerInput();
}

void ADRSPlayerCharacter::InitializePlayerInput()
{
	check(IsValid(InputComponent));
	
	const APlayerController* PlayerController = GetController<APlayerController>();
	check(IsValid(PlayerController));

	const ULocalPlayer* LocalPlayer = PlayerController->GetLocalPlayer();
	check(IsValid(LocalPlayer));
	
	UEnhancedInputLocalPlayerSubsystem* Subsystem = LocalPlayer->GetSubsystem<UEnhancedInputLocalPlayerSubsystem>();
	check(IsValid(Subsystem));
	
	// Clear any existing mappings to prevent duplicate bindings when respawning or possessing a new character.
	Subsystem->ClearAllMappings(); 
	
	if (!DefaultInputMappingContext.IsNull())
	{
		FModifyContextOptions MappingOptions = {};
		MappingOptions.bIgnoreAllPressedKeysUntilRelease = true;
		
		constexpr int32 MappingPriority = 1; // Default priority, can be adjusted if you have multiple mapping contexts.
		Subsystem->AddMappingContext(DefaultInputMappingContext.LoadSynchronous(), MappingPriority, MappingOptions);

		if (IsValid(DefaultInputConfig))
		{
			BindInputActions();
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("DefaultInputMappingContext is null on %s. No input mappings have been added."), *GetName());
	}
}

void ADRSPlayerCharacter::BindInputActions()
{	
	checkf(IsValid(DefaultInputConfig), TEXT("DefaultInputConfig is not valid on %s. Cannot bind input actions."), *GetName());
	
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);
	
	/* Iterate through the ability input actions defined in the DefaultInputConfig and bind them to functions on this character.
	 * Each input action will be bound to the OnAbilityInputTriggered function, and the associated InputTag will be passed as a parameter to identify which action was triggered.
	 * From within the AbilitySystemComponent */
	for (const auto& ActionEntry : DefaultInputConfig->GetAbilityInputActions())
	{
		checkf(!ActionEntry.InputAction.IsNull(), TEXT("InputAction entry %s in DefaultInputConfig on %s is null."), *ActionEntry.InputTag.ToString(), *GetName());
		
		const UInputAction* InputAction = ActionEntry.InputAction.LoadSynchronous();
		check(IsValid(InputAction));
		
		// Bind the input action to the OnAbilityInputTriggered function, passing the associated InputTag as a parameter.
		EnhancedInputComponent->BindAction(InputAction, ETriggerEvent::Triggered, this, &ADRSPlayerCharacter::OnAbilityInputTriggered, ActionEntry.InputTag);
	}
	
	// Bind other non-ability input actions here as needed, for example movement and looking input.
	if (IsValid(JumpInputAction))
	{
		EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpInputAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
	}
	
	if (IsValid(MoveInputAction))
	{
		EnhancedInputComponent->BindAction(MoveInputAction, ETriggerEvent::Triggered, this, &ADRSPlayerCharacter::OnMoveInput);
	}

	if (IsValid(LookInputAction))
	{
		EnhancedInputComponent->BindAction(LookInputAction, ETriggerEvent::Triggered, this, &ADRSPlayerCharacter::OnLookInput);
	}
}

void ADRSPlayerCharacter::OnMoveInput(const FInputActionValue& InputValue)
{
	const FVector2D MovementVector = InputValue.Get<FVector2D>();
	
	FRotator ControlRotation = GetControlRotation();
	ControlRotation.Pitch = 0.f; // We don't want pitch to affect movement direction.
	
	const FVector RightVector = FRotationMatrix(ControlRotation).GetScaledAxis(EAxis::Y);
	const FVector ForwardVector = FRotationMatrix(ControlRotation).GetScaledAxis(EAxis::X);
	
	AddMovementInput(RightVector, MovementVector.X);
	AddMovementInput(ForwardVector, MovementVector.Y);
}

void ADRSPlayerCharacter::OnLookInput(const FInputActionValue& InputValue)
{
	const FVector2D LookAxisVector = InputValue.Get<FVector2D>();
	AddControllerYawInput(LookAxisVector.X);
	AddControllerPitchInput(LookAxisVector.Y);
}

void ADRSPlayerCharacter::OnAbilityInputTriggered(const FGameplayTag InputTag)
{
	check(InputTag.IsValid());
	checkf(IsValid(AbilitySystemComponent), TEXT("AbilitySystemComponent is not valid on %s. Cannot trigger ability input."), *GetName());
	
	AbilitySystemComponent->NotifyAbilityInputTriggered(InputTag);
}
