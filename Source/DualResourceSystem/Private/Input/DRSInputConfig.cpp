// Fill out your copyright notice in the Description page of Project Settings.

#include "Input/DRSInputConfig.h"

#include "InputAction.h"

UDRSInputConfig::UDRSInputConfig()
{
}

const UInputAction* UDRSInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag, const bool bLogNotFound) const
{
	for (const FDRSInputAction& Action : AbilityInputActions)
	{
		if (!Action.InputAction.IsNull() && Action.InputTag == InputTag)
		{
			return Action.InputAction.LoadSynchronous();
		}
	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("Can't find AbilityInputAction for InputTag [%s] on InputConfig [%s]."), *InputTag.ToString(), *GetNameSafe(this));
	}

	return nullptr;
}