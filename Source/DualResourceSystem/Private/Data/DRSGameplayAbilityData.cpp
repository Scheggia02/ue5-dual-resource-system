// Fill out your copyright notice in the Description page of Project Settings.


#include "Data/DRSGameplayAbilityData.h"

UDRSGameplayAbilityData::UDRSGameplayAbilityData()
{
}

bool UDRSGameplayAbilityData::IsValid() const
{
	// An ability is considered valid if it has a non-null class and a level greater than 0. 
	// The input tag is optional and can be empty. Ideally there isn't a need to tie validity of the ability to an input.
	return !AbilityClass.IsNull() && AbilityLevel > 0;
}
