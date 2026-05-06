// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

/**
 * Static library of utility functions for the Dual Resource System.
 */
class FDRSResourceLibrary
{
public:
	static bool CanCoverCost(float CurrentHealth, float CurrentMana, float CostAmount, float CriticalHealthThreshold, bool bIsOverdrawEnabled);
	static float GetCostHealth(float CurrentHealth, float CostAmount, float CriticalHealthThreshold, bool bIsOverdrawEnabled);
	static float GetCostMana(float CurrentMana, float CostAmount);
};