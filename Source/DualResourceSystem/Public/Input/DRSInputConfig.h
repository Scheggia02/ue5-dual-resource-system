// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataAsset.h"
#include "GameplayTagContainer.h"

#include "DRSInputConfig.generated.h"

class UInputAction;
class UObject;
struct FFrame;

/**
 * Maps an Enhanced Input action asset to a gameplay tag used by the ability input system.
 *
 * Player characters use these mappings to translate input callbacks into gameplay tags, then
 * forward those tags to the ability system component so matching granted abilities can activate.
 */
USTRUCT(BlueprintType)
struct FDRSInputAction
{
	GENERATED_BODY()

public:

	/** Enhanced Input action asset to bind. Loaded synchronously when input bindings are created. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<const UInputAction> InputAction = nullptr;

	/** Gameplay tag sent to the ability system when this input action is triggered. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
};

/**
 * Data asset that defines gameplay-tag based input bindings for a player character.
 *
 * The config is treated as read-only at runtime. Each configured ability input action is bound by
 * ADRSPlayerCharacter and routed to abilities whose specs contain the same input tag.
 */
UCLASS(BlueprintType, Const)
class UDRSInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	/** Creates the input config data asset. */
	UDRSInputConfig();

	/**
	 * Finds the input action mapped to the provided gameplay tag.
	 *
	 * @param InputTag Gameplay input tag to search for.
	 * @param bLogNotFound If true, logs an error when no matching action exists.
	 * @return The loaded input action for the tag, or nullptr when not found.
	 */
	UFUNCTION(BlueprintCallable, Category = "AD|Pawn")
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = true) const;

	/** Returns all configured ability input action mappings. */
	const TArray<FDRSInputAction>& GetAbilityInputActions() const { return AbilityInputActions; }
	
protected:
	/** Input actions that should be bound and routed to abilities through gameplay tags. */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
	TArray<FDRSInputAction> AbilityInputActions;
};