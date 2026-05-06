// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DRSCharacterConfigData.generated.h"

class UGameplayEffect;

/**
 * Primary data asset that defines the default gameplay setup for a DRS character.
 *
 * ADRSCharacter loads this asset by primary asset id when possessed, then uses it to grant default
 * abilities and apply an initial Gameplay Effect for attribute values.
 */
UCLASS()
class DUALRESOURCESYSTEM_API UDRSCharacterConfigData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	/** Creates the character config data asset. */
	UDRSCharacterConfigData();

	/** Returns the primary asset ids of ability data assets granted during character initialization. */
	FORCEINLINE TArray<FPrimaryAssetId> GetDefaultAbilities() const { return DefaultAbilities; }
	/** Returns the Gameplay Effect class applied to initialize or modify default attributes. */
	FORCEINLINE TSoftClassPtr<UGameplayEffect> GetDefaultAttributeSetEffect() const { return DefaultAttributeSetEffect; }
	
protected:
	/** Ability data assets granted to the character after this config has loaded. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Config", meta = (AllowedTypes = "DRSGameplayAbilityData"))
	TArray<FPrimaryAssetId> DefaultAbilities;
	
	/** Gameplay Effect applied to the character's ability system component during initialization. */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Config")
	TSoftClassPtr<UGameplayEffect> DefaultAttributeSetEffect;
};
