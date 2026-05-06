// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "DRSAbilitySystemComponent.generated.h"


class UDRSGameplayAbilityData;
class UDRSGameplayAbility;

/**
 * Project-specific Ability System Component used by the Dual Resource System.
 *
 * Extends Unreal's Gameplay Ability System component with helper functions for:
 * - granting abilities from primary asset ids or ability data assets;
 * - binding granted abilities to gameplay-tag based input triggers;
 * - applying a Gameplay Effect to initialize or modify this component's attributes.
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DUALRESOURCESYSTEM_API UDRSAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	/** Creates the ability system component. */
	UDRSAbilitySystemComponent();

	/**
	 * Asynchronously loads ability data primary assets and grants the abilities when loading completes.
	 *
	 * @param AbilitiesToGrant Primary asset ids that must resolve to UDRSGameplayAbilityData assets.
	 */
	UFUNCTION(BlueprintCallable, Category = "Abilities")
	void GrantAbilitiesById(const TArray<FPrimaryAssetId>& AbilitiesToGrant);

	/**
	 * Grants every ability described by the provided ability data assets.
	 *
	 * Each asset is expected to be valid and to reference a loadable UDRSGameplayAbility class.
	 *
	 * @param AbilitiesToGrant Already-loaded ability data assets to grant to this component.
	 */
	void GrantAbilitiesByAsset(const TArray<UDRSGameplayAbilityData*>& AbilitiesToGrant);
	
	/**
	 * Grants a single ability from an ability data asset.
	 *
	 * The ability class is loaded synchronously, then granted with the configured ability level.
	 * The asset's input tag is copied into the ability spec's dynamic source tags so input events
	 * can later activate the ability through NotifyAbilityInputTriggered().
	 *
	 * @param AbilityAssetToGrant Ability data asset that describes the ability class, level, and input tag.
	 */
	void GrantAbilityByAsset(const UDRSGameplayAbilityData* AbilityAssetToGrant);
	
	/**
	 * Attempts to activate all granted abilities whose dynamic source tags exactly match the input tag.
	 *
	 * This is intended to be called by character/controller input code after translating an input action
	 * into a gameplay tag. Invalid tags are ignored with a warning.
	 *
	 * @param InputTag Gameplay tag representing the triggered input action.
	 */
	UFUNCTION(Blueprintable, Category = "Abilities")
	void NotifyAbilityInputTriggered(FGameplayTag InputTag);

	/**
	 * Loads and applies a Gameplay Effect class to this component to initialize or modify attributes.
	 *
	 * The effect is applied to self at level 1 and uses this component as the source object.
	 *
	 * @param AttributeSetEffectClass Soft class pointer to the Gameplay Effect to apply.
	 */
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void ApplyAttributeSetEffect(TSoftClassPtr<UGameplayEffect> AttributeSetEffectClass);

protected:
	/**
	 * Callback invoked after primary ability assets requested by GrantAbilitiesById() finish loading.
	 *
	 * @param AbilitiesToGrant Primary asset ids that were requested and should now be available from the asset manager.
	 */
	UFUNCTION()
	void OnAbilityPrimaryAssetsLoaded(TArray<FPrimaryAssetId> AbilitiesToGrant);
};
