// Fill out your copyright notice in the Description page of Project Settings.

#include "Systems/Resource/DRSResourceLibrary.h"

bool FDRSResourceLibrary::CanCoverCost(const float CurrentHealth, const float CurrentMana, const float CostAmount, const float CriticalHealthThreshold, const bool bIsOverdrawEnabled)
{
	// If overdraw is enabled, we can cover the entire cost with health, so we just need to check if current health is greater than the cost amount.
	if (bIsOverdrawEnabled)
	{
		return CurrentHealth > CostAmount;
	}
	
	// If overdraw is not enabled, we can only cover part of the cost with mana, then health up until critical level.
	const float ManaAvailableForCost = FMath::Min(CurrentMana, CostAmount);
	const float RemainingCostAfterMana = CostAmount - ManaAvailableForCost;
	const float HealthAvailableForCost = CurrentHealth - CriticalHealthThreshold;
	return HealthAvailableForCost >= RemainingCostAfterMana;
}

float FDRSResourceLibrary::GetCostHealth(const float CurrentHealth, const float CostAmount, const float CriticalHealthThreshold, const bool bIsOverdrawEnabled)
{
	// If overdraw is enabled, we can cover the entire cost with health, so return the full cost amount.
	if (bIsOverdrawEnabled)
	{
		return CostAmount;
	}
	
	// If overdraw is not enabled, we can only cover part of the cost with health, so return the difference between current health and the critical health threshold as the amount of the cost covered by health.
	const float HealthAvailableForCost = CurrentHealth - CriticalHealthThreshold;
	return FMath::Min(HealthAvailableForCost, CostAmount);
}

float FDRSResourceLibrary::GetCostMana(const float CurrentMana, const float CostAmount)
{
	// If mana is greater than or equal to the cost, we can cover the entire cost with mana, so return the full cost amount.
	if (CurrentMana >= CostAmount)
	{
		return CostAmount;
	}
	
	// If mana is less than the cost, we can only cover part of the cost with mana, so return the remaining mana as the amount of the cost covered by mana.
	return CurrentMana;
}
