// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DRSGameplayAbility.generated.h"

class ADRSCharacter;
/**
 * Base gameplay ability class for abilities used by the Dual Resource System.
 *
 * Project abilities should derive from this class so shared DRS ability behavior can be added in
 * one place later without changing every ability asset or Blueprint class.
 */
UCLASS()
class DUALRESOURCESYSTEM_API UDRSGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	UDRSGameplayAbility();
	
	virtual bool CanActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags = nullptr, const FGameplayTagContainer* TargetTags = nullptr, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual bool CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, OUT FGameplayTagContainer* OptionalRelevantTags = nullptr) const override;
	virtual void ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Ability|Execution")
	bool bCanActivateWhenOutOfHealth = false;
	
	UPROPERTY(EditDefaultsOnly, Category = "Ability|Cost")
	bool bCanActivateWithOverdraw = false;
	
	/* The amount of resource cost this ability requires. This is a flat value that will be interpreted by the resource execution component, 
	 * it can represent health, mana, or a combination of both depending on the execution rules defined in that component. 
	 * If the cost amount is zero or very close to zero, we will skip checking for a resource execution component and just allow the ability to activate. */
	UPROPERTY(EditDefaultsOnly, Category = "Ability|Cost", meta = (ClampMin = "0.0", UIMin = "0.0"))
	float CostAmount = 0.f;
	
	
	UFUNCTION(BlueprintPure, Category = "Ability")
	ADRSCharacter* GetDRSCharacterFromActorInfo() const;
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
};
