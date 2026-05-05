// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DRSCharacterConfigData.generated.h"

class UAttributeSet;
class UDRSGameplayAbility;

/**
 * 
 */
UCLASS()
class DUALRESOURCESYSTEM_API UDRSCharacterConfigData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UDRSCharacterConfigData();

	TArray<TSoftClassPtr<UDRSGameplayAbility>> GetDefaultAbilities() const { return DefaultAbilities; }
	TSoftClassPtr<UAttributeSet> GetDefaultAttributeSet() const { return DefaultAttributeSet; }
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Config")
	TArray<TSoftClassPtr<UDRSGameplayAbility>> DefaultAbilities;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Config")
	TSoftClassPtr<UAttributeSet> DefaultAttributeSet;
};
