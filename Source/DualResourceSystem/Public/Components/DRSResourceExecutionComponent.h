// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DRSResourceExecutionComponent.generated.h"


class UGameplayEffect;
class UDRSAbilitySystemComponent;
/**
 * Actor component reserved for executing resource-related gameplay behavior.
 *
 * The component is attached to DRS characters as an extension point for resource spending,
 * regeneration, or other resource execution rules. It currently performs no per-frame ticking.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUALRESOURCESYSTEM_API UDRSResourceExecutionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDRSResourceExecutionComponent();

	UFUNCTION(BlueprintCallable, Category = "Attributes")
	void CommitAbilityCost(float CostAmount);
	
	UFUNCTION(BlueprintCallable, Category = "Attributes")
	bool CanCoverAbilityCost(float CostAmount) const;
	
	UFUNCTION(BlueprintPure, Category = "Attributes")
	void GetCurrentResourceValues(float& OutHealth, float& OutMana) const;
	
	virtual void BeginPlay() override;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category = "Resource Execution")
	TSoftClassPtr<UGameplayEffect> ResourceCostGameplayEffectClass;
	
private:
	float GetCurrentHealth() const;
	float GetCriticalHealth() const;
	float GetCurrentMana() const;
	
	UDRSAbilitySystemComponent* GetAbilitySystemComponent() const;
};
