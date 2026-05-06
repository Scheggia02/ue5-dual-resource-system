// Fill out your copyright notice in the Description page of Project Settings.

#include "AbilitySystem/Abilities//DRSGameplayAbility.h"

#include "Characters/DRSCharacter.h"
#include "Components/DRSAbilitySystemComponent.h"
#include "Components/DRSHealthComponent.h"
#include "Components/DRSResourceExecutionComponent.h"

UDRSGameplayAbility::UDRSGameplayAbility()
{
}

ADRSCharacter* UDRSGameplayAbility::GetDRSCharacterFromActorInfo() const
{
	if (CurrentActorInfo && CurrentActorInfo->OwnerActor.IsValid())
	{
		return Cast<ADRSCharacter>(CurrentActorInfo->OwnerActor.Get());
	}
	return nullptr;
}

void UDRSGameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo))
	{			
		// If committing the ability fails, we end it so it doesn't remain in an active but non-committed state. 
		// We mark it as cancelled since failure to commit usually means the ability's cost couldn't be paid for

		constexpr bool bReplicateEndAbility = true;
		constexpr bool bWasCancelled = true;
		EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	}
	
	// If the ability was successfully committed
}

bool UDRSGameplayAbility::CanActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                             const FGameplayAbilityActorInfo* ActorInfo, const FGameplayTagContainer* SourceTags,
                                             const FGameplayTagContainer* TargetTags, FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!ActorInfo || !ActorInfo->AbilitySystemComponent.IsValid())
	{
		return false;
	}

	// If the character is out of health, only allow activation if bCanActivateWhenOutOfHealth is true on this ability.

	if (!bCanActivateWhenOutOfHealth)
	{
		const auto* ActorComponent = ActorInfo->OwnerActor.Get()->GetComponentByClass(UDRSHealthComponent::StaticClass());
		const auto* HealthComponent = Cast<UDRSHealthComponent>(ActorComponent);
		if (IsValid(HealthComponent) && HealthComponent->IsDeadOrDying())
		{
			return false;
		}
	}
	
	return Super::CanActivateAbility(Handle, ActorInfo, SourceTags, TargetTags, OptionalRelevantTags);
}

bool UDRSGameplayAbility::CheckCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	FGameplayTagContainer* OptionalRelevantTags) const
{
	if (!ActorInfo || !ActorInfo->AbilitySystemComponent.IsValid())
	{
		return false;
	}
	
	if (FMath::IsNearlyZero(CostAmount))
	{
		// If the cost amount is zero or very close to zero, we can skip checking for a resource execution component and just allow the ability to activate.
		return true;
	}

	const auto* ActorComponent = ActorInfo->OwnerActor.Get()->GetComponentByClass(UDRSResourceExecutionComponent::StaticClass());
	if (const auto* ResourceExecutionComponent = Cast<UDRSResourceExecutionComponent>(ActorComponent); IsValid(ResourceExecutionComponent))
	{
		return ResourceExecutionComponent->CanCoverAbilityCost(CostAmount);
	}
	
	return false;
}

void UDRSGameplayAbility::ApplyCost(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo) const
{
	Super::ApplyCost(Handle, ActorInfo, ActivationInfo);
	
	if (FMath::IsNearlyZero(CostAmount))
	{
		// If the cost amount is zero or very close to zero, we can skip applying cost since there is no cost to apply.
		return;
	}
	
	auto* ActorComponent = ActorInfo->OwnerActor.Get()->GetComponentByClass(UDRSResourceExecutionComponent::StaticClass());
	if (auto* ResourceExecutionComponent = Cast<UDRSResourceExecutionComponent>(ActorComponent); IsValid(ResourceExecutionComponent))
	{		
		ResourceExecutionComponent->CommitAbilityCost(CostAmount);
	}
}
