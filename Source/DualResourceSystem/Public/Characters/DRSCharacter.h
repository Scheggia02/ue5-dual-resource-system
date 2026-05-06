// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DRSCharacter.generated.h"

class UDRSCharacterConfigData;
class UDRSAbilitySystemComponent;
class UDRSResourceExecutionComponent;
class UDRSCharacterAttributeSet;

/**
 * Base character for actors that participate in the Dual Resource System.
 *
 * Owns the ability system component, the character attribute set, and the resource execution
 * component. On possession, it loads a character config data asset and uses that config to grant
 * default abilities and apply the default attribute initialization Gameplay Effect.
 */
UCLASS()
class DUALRESOURCESYSTEM_API ADRSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	/** Creates the character and its DRS gameplay components. */
	ADRSCharacter();

	/** Standard actor initialization hook. */
	virtual void BeginPlay() override;
	
protected:
	/** Primary asset id of the character configuration loaded when the character is possessed. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Configuration", meta = (AllowedTypes = "DRSCharacterConfigData"))
	FPrimaryAssetId CharacterConfigDataId;
	
	/** Ability system component responsible for granted abilities, effects, and attributes. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UDRSAbilitySystemComponent> AbilitySystemComponent;

	/** Character attribute set registered with the ability system component. */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	TObjectPtr<UDRSCharacterAttributeSet> AttributeSet;
	
	/** Component reserved for resource execution behavior. */
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UDRSResourceExecutionComponent> ResourceExecutionComponent;

	/** Loaded character configuration asset used during ability system initialization. */
	UPROPERTY(Transient)
	TObjectPtr<UDRSCharacterConfigData> CharacterConfigData;
	
public:
	
	/** Loads character configuration after the character receives a controller. */
	virtual void PossessedBy(AController* NewController) override;
	/** Allows derived classes to bind input while preserving base character setup. */
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	/** Requests the configured character config asset from the asset manager. */
	void LoadCharacterConfigData();
	/** Reads the loaded character config asset and begins ability system initialization. */
	void ApplyCharacterConfigData();
	/** Initializes ability actor info, grants default abilities, and applies default attributes. */
	void InitializeAbilitySystem();
};
