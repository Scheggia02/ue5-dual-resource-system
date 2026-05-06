// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRSGameplayAbility.h"
#include "DRS_GA_Dash.generated.h"

class UAbilityTask_ApplyRootMotionConstantForce;
/**
 * 
 */
UCLASS()
class DUALRESOURCESYSTEM_API UDRS_GA_Dash : public UDRSGameplayAbility
{
	GENERATED_BODY()
	
public:
	UDRS_GA_Dash();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Dash")
	float DashStrength = 2000.f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Dash")
	float DashDuration = 0.5f;
	
	UPROPERTY(Transient)
	UAbilityTask_ApplyRootMotionConstantForce* DashMovementTask = nullptr;
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	
private:
	UFUNCTION()
	void OnDashFinished();
	
	void PerformDash();
};
