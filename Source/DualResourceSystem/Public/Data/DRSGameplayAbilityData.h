// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DRSGameplayAbilityData.generated.h"

class UDRSGameplayAbility;
/**
 * 
 */
UCLASS()
class DUALRESOURCESYSTEM_API UDRSGameplayAbilityData : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UDRSGameplayAbilityData();
	
	bool IsValid() const;
	
	FORCEINLINE TSoftClassPtr<UDRSGameplayAbility> GetAbilityClass() const { return AbilityClass; }
	FORCEINLINE FGameplayTag GetAbilityInputTag() const { return AbilityInputTag; }
	FORCEINLINE int32 GetAbilityLevel() const { return AbilityLevel; }
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	TSoftClassPtr<UDRSGameplayAbility> AbilityClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	FGameplayTag AbilityInputTag = FGameplayTag::EmptyTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Ability")
	int32 AbilityLevel = 1;
};
