// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DRSCharacterConfigData.generated.h"

class UGameplayEffect;

/**
 * 
 */
UCLASS()
class DUALRESOURCESYSTEM_API UDRSCharacterConfigData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UDRSCharacterConfigData();

	FORCEINLINE TArray<FPrimaryAssetId> GetDefaultAbilities() const { return DefaultAbilities; }
	FORCEINLINE TSoftClassPtr<UGameplayEffect> GetDefaultAttributeSetEffect() const { return DefaultAttributeSetEffect; }
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Config", meta = (AllowedTypes = "DRSGameplayAbilityData"))
	TArray<FPrimaryAssetId> DefaultAbilities;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Config")
	TSoftClassPtr<UGameplayEffect> DefaultAttributeSetEffect;
};
