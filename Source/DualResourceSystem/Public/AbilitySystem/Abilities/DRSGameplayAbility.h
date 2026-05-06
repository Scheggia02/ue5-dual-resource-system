// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "DRSGameplayAbility.generated.h"

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
	
};
