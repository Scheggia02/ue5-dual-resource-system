// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DRSResourceExecutionComponent.h"

#include "Attributes/DRSCharacterAttributeSet.h"
#include "Components/DRSAbilitySystemComponent.h"
#include "Input/DRSGameplayTags.h"
#include "Systems/Resource/DRSResourceLibrary.h"

UDRSResourceExecutionComponent::UDRSResourceExecutionComponent()
{
	// No need to tick every frame for this component, so we disable ticking.
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UDRSResourceExecutionComponent::CommitAbilityCost(const float CostAmount)
{
	checkf(CostAmount > 0.f && !FMath::IsNearlyZero(CostAmount), TEXT("Cost amount should be positive and not nearly zero. Received: %f"), CostAmount);
	
	UDRSAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponent();
	if (!IsValid(AbilitySystemComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("DRSResourceExecutionComponent: No ability system component found on owner actor %s. Cannot commit ability cost."), *GetOwner()->GetName());
		return;
	}
	
	check(!ResourceCostGameplayEffectClass.IsNull());

	const TSubclassOf<UGameplayEffect> LoadedCostEffect = ResourceCostGameplayEffectClass.LoadSynchronous();
	
	FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponent->MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	
	constexpr int32 DefaultEffectLevel = 1;
	const FGameplayEffectSpecHandle NewSpec = AbilitySystemComponent->MakeOutgoingSpec(LoadedCostEffect, DefaultEffectLevel, EffectContextHandle);
	
	// We use SetByCaller to pass the cost amount to the gameplay effect, which allows us to use the same gameplay effect for different abilities with different costs.
	NewSpec.Data->SetSetByCallerMagnitude(DRSGameplayTags::SetByCaller_Cost, CostAmount);
	
	// Apply the gameplay effect to self to execute the cost deduction.
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*NewSpec.Data.Get());
}

void UDRSResourceExecutionComponent::GetCurrentResourceValues(float& OutHealth, float& OutMana) const
{
	OutHealth = GetCurrentHealth();
	OutMana = GetCurrentMana();
}

bool UDRSResourceExecutionComponent::CanCoverAbilityCost(const float CostAmount) const
{
	checkf(CostAmount >= 0.f, TEXT("Cost amount should not be negative. Received: %f"), CostAmount);
	if (FMath::IsNearlyZero(CostAmount))
	{
		// If the cost amount is zero or very close to zero, we can skip checking for a resource execution component and just allow the ability to activate.
		return true;
	}
	
	UDRSAbilitySystemComponent* AbilitySystemComponent = GetAbilitySystemComponent();
	if (!IsValid(AbilitySystemComponent))
	{
		UE_LOG(LogTemp, Warning, TEXT("DRSResourceExecutionComponent: No ability system component found on owner actor %s. Cannot check if ability cost can be covered."), *GetOwner()->GetName());
		return false;
	}
	
	const float CurrentHealth = GetCurrentHealth();
	const float CurrentMana = GetCurrentMana();
	const float CriticalHealthThreshold = GetCriticalHealth();
	const bool bIsOverdrawEnabled = AbilitySystemComponent->HasMatchingGameplayTag(DRSGameplayTags::Status_Overdraw);
	
	return FDRSResourceLibrary::CanCoverCost(CurrentHealth, CurrentMana, CostAmount, CriticalHealthThreshold, bIsOverdrawEnabled);
}

void UDRSResourceExecutionComponent::BeginPlay()
{
	Super::BeginPlay();
	
	checkf(!ResourceCostGameplayEffectClass.IsNull(), TEXT("ResourceCostGameplayEffectClass must be set in %s"), *GetName());
}

float UDRSResourceExecutionComponent::GetCurrentHealth() const
{
	if (const auto* AbilitySystemComponent = GetAbilitySystemComponent(); IsValid(AbilitySystemComponent))
	{
		return AbilitySystemComponent->GetNumericAttribute(UDRSCharacterAttributeSet::GetHealthAttribute());
	}
	return 0.f;
}

float UDRSResourceExecutionComponent::GetCriticalHealth() const
{
	if (const auto* AbilitySystemComponent = GetAbilitySystemComponent(); IsValid(AbilitySystemComponent))
	{
		return AbilitySystemComponent->GetNumericAttribute(UDRSCharacterAttributeSet::GetCriticalHealthAttribute());
	}
	return 0.f;
}

float UDRSResourceExecutionComponent::GetCurrentMana() const
{
	if (const auto* AbilitySystemComponent = GetAbilitySystemComponent(); IsValid(AbilitySystemComponent))
	{
		return AbilitySystemComponent->GetNumericAttribute(UDRSCharacterAttributeSet::GetManaAttribute());
	}
	return 0.f;
}

UDRSAbilitySystemComponent* UDRSResourceExecutionComponent::GetAbilitySystemComponent() const
{
	if (const auto* Owner = GetOwner(); IsValid(Owner))
	{
		return Cast<UDRSAbilitySystemComponent>(Owner->GetComponentByClass(UDRSAbilitySystemComponent::StaticClass()));
	}
	return nullptr;
}
