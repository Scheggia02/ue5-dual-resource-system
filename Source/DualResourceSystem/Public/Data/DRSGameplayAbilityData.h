// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DRSGameplayAbilityData.generated.h"

class UDRSGameplayAbility;

/**
 * Primary data asset that describes an ability grant for the Dual Resource System.
 *
 * Character config assets reference these assets by primary asset id. When granted, the ability
 * system component loads the ability class, creates an ability spec at the configured level, and
 * stores the optional input tag in the spec's dynamic source tags for input-driven activation.
 */
UCLASS()
class DUALRESOURCESYSTEM_API UDRSGameplayAbilityData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	/** Creates the ability data asset. */
	UDRSGameplayAbilityData();
	
	/**
	 * Checks whether this data asset can grant an ability.
	 *
	 * A valid asset must reference an ability class and have a level greater than zero.
	 * The input tag is optional and may be empty for non-input-triggered abilities.
	 */
	bool IsValid() const;
	
	/** Returns the soft class reference for the gameplay ability to grant. */
	FORCEINLINE TSoftClassPtr<UDRSGameplayAbility> GetAbilityClass() const { return AbilityClass; }
	/** Returns the optional input tag used to activate this ability from player input. */
	FORCEINLINE FGameplayTag GetAbilityInputTag() const { return AbilityInputTag; }
	/** Returns the ability level used when creating the gameplay ability spec. */
	FORCEINLINE int32 GetAbilityLevel() const { return AbilityLevel; }
	
protected:
	/** Gameplay ability class granted by this data asset. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	TSoftClassPtr<UDRSGameplayAbility> AbilityClass;

	/** Optional input tag that links this ability to an input action mapping. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	FGameplayTag AbilityInputTag = FGameplayTag::EmptyTag;
	
	/** Level assigned to the ability spec when the ability is granted. Must be greater than zero. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	int32 AbilityLevel = 1;
};
