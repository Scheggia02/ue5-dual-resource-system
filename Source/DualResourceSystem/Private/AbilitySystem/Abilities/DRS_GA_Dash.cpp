// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Abilities/DRS_GA_Dash.h"

#include "Abilities/Tasks/AbilityTask_ApplyRootMotionConstantForce.h"
#include "Characters/DRSCharacter.h"
#include "Input/DRSGameplayTags.h"

UDRS_GA_Dash::UDRS_GA_Dash()
{
	// Dash cannot be performed if the character is out of health, since it's a mobility ability that would allow the character to escape danger without any risk of dying.
	bCanActivateWhenOutOfHealth = false;
	CostAmount = 20.0f;
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	
	ActivationOwnedTags.AddTag(DRSGameplayTags::Ability_Dash);
	ActivationBlockedTags.AddTag(DRSGameplayTags::Ability_Dash);
	
	// This ability is not re-triggerable, since it would allow the character to dash repeatedly without any cooldown by simply tapping the input button.
	bRetriggerInstancedAbility = false;
}

void UDRS_GA_Dash::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if (bIsAbilityEnding)
	{
		return;
	}

	PerformDash();
}

void UDRS_GA_Dash::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	if (IsValid(DashMovementTask))
	{
		DashMovementTask->EndTask();
		DashMovementTask = nullptr;
	}
	
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UDRS_GA_Dash::OnDashFinished()
{
	EndAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true, false);
}

void UDRS_GA_Dash::PerformDash()
{
	const auto* OwnerCharacter = GetDRSCharacterFromActorInfo();
	if (!IsValid(OwnerCharacter))
	{
		return;
	}
	
	const FVector DashDirection = OwnerCharacter->GetActorForwardVector();
	
	DashMovementTask = UAbilityTask_ApplyRootMotionConstantForce::ApplyRootMotionConstantForce(this, NAME_None, DashDirection, DashStrength, DashDuration, false, nullptr, ERootMotionFinishVelocityMode::SetVelocity, FVector::ZeroVector, 0.0f, false);
	DashMovementTask->OnFinish.AddDynamic(this, &UDRS_GA_Dash::OnDashFinished);
	DashMovementTask->ReadyForActivation();
}
