// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DRSHealthComponent.h"

#include "Attributes/DRSCharacterAttributeSet.h"
#include "Components/DRSAbilitySystemComponent.h"

UDRSHealthComponent::UDRSHealthComponent()
{
	// Tick is not needed for this component, so we disable it to save performance.
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

bool UDRSHealthComponent::IsDeadOrDying() const
{
	return GetCurrentHealth() <= 0.f;
}

float UDRSHealthComponent::GetCurrentHealth() const
{
	if (const UDRSAbilitySystemComponent* AbilitySystemComp = GetOwnerAbilitySystemComponent(); IsValid(AbilitySystemComp))
	{
		return AbilitySystemComp->GetNumericAttribute(UDRSCharacterAttributeSet::GetHealthAttribute());
	}
	return 0.f;
}

UDRSAbilitySystemComponent* UDRSHealthComponent::GetOwnerAbilitySystemComponent() const
{
	if (const AActor* Owner = GetOwner(); IsValid(Owner))
	{
		return Owner->FindComponentByClass<UDRSAbilitySystemComponent>();
	}
	return nullptr;
}

