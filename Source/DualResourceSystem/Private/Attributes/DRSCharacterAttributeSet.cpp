// Fill out your copyright notice in the Description page of Project Settings.


#include "Attributes/DRSCharacterAttributeSet.h"

#include "GameplayEffectExtension.h"
#include "Input/DRSGameplayTags.h"
#include "Systems/Resource/DRSResourceLibrary.h"

UDRSCharacterAttributeSet::UDRSCharacterAttributeSet()
{
	
}

bool UDRSCharacterAttributeSet::PreGameplayEffectExecute(FGameplayEffectModCallbackData& Data)
{
	// Save the current health
	HealthPreAttributeChange = GetHealth();
	
	return Super::PreGameplayEffectExecute(Data);
}

void UDRSCharacterAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if (Data.EvaluatedData.Attribute == GetResourceCostAttribute())
	{ 
		HandleCostExecution(Data);
	}
}

void UDRSCharacterAttributeSet::HandleCostExecution(const FGameplayEffectModCallbackData& Data)
{
	const float CostValue = GetResourceCost();
	if (CostValue <= 0.f)
	{
		// If the cost value is zero or negative, we can skip executing the cost since it doesn't make sense to execute a non-positive cost.
		return;
	}
	
	const bool bIsOverdrawEnabled = IsOverdrawEnabled(Data);
	
	const float ManaValue = GetMana();
	const float ManaCost = FDRSResourceLibrary::GetCostMana(ManaValue, CostValue);
	ApplyManaCost(ManaCost);
	
	const float HealthValue = GetHealth();
	const float HealthCost = FDRSResourceLibrary::GetCostHealth(HealthValue, CostValue, GetCriticalHealth(), bIsOverdrawEnabled);
	ApplyHealthCost(HealthCost);
}

void UDRSCharacterAttributeSet::CheckForHealthChange(const FGameplayEffectModCallbackData& Data)
{
	if (GetHealth() == HealthPreAttributeChange)
	{	
		// If health didn't actually change, we can skip broadcasting the event.
		return;
	}
	
	const FGameplayEffectContextHandle& EffectContext = Data.EffectSpec.GetEffectContext();
	AActor* Instigator = EffectContext.GetOriginalInstigator();
	AActor* Causer = EffectContext.GetEffectCauser();
	
	if (OnHealthChanged.IsBound())
	{
		OnHealthChanged.Broadcast(Instigator, Causer, &Data.EffectSpec, Data.EvaluatedData.Magnitude, HealthPreAttributeChange, GetHealth());
	}
	
	if (GetHealth() <= 0.0f && HealthPreAttributeChange > 0.0f && OnOutOfHealth.IsBound())
	{
		OnOutOfHealth.Broadcast(Instigator, Causer, &Data.EffectSpec, Data.EvaluatedData.Magnitude, HealthPreAttributeChange, GetHealth());
	}
}

bool UDRSCharacterAttributeSet::IsOverdrawEnabled(const FGameplayEffectModCallbackData& Data)
{
	return Data.Target.HasMatchingGameplayTag(DRSGameplayTags::Status_Overdraw);
}

void UDRSCharacterAttributeSet::ApplyHealthCost(const float Amount)
{
	if (Amount <= 0.f)
	{
		// If the amount is zero or negative, we can skip applying the cost since it doesn't make sense to apply a non-positive cost.
		return;
	}
	
	const float NewHealth = FMath::Max(GetHealth() - Amount, 0.f);
	SetHealth(NewHealth);
}

void UDRSCharacterAttributeSet::ApplyManaCost(const float Amount)
{
	if (Amount <= 0.f)
	{
		// If the amount is zero or negative, we can skip applying the cost since it doesn't make sense to apply a non-positive cost.
		return;
	}
	
	const float NewMana = FMath::Max(GetMana() - Amount, 0.f);
	SetMana(NewMana);
}
