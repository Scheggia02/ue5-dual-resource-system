// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DRSAttributeSet.h"
#include "AbilitySystemComponent.h"
#include "DRSCharacterAttributeSet.generated.h"

/**
 * This is the attribute set class for our character, it is used to define attributes that are specific to our character,
 * such as health, mana, etc. It inherits from UDRSAttributeSet, which defines attributes that are common to all characters in our game.
 */
UCLASS()
class DUALRESOURCESYSTEM_API UDRSCharacterAttributeSet : public UDRSAttributeSet
{
	GENERATED_BODY()
	
public:
	UDRSCharacterAttributeSet();
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UDRSCharacterAttributeSet, Health)
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes")
	FGameplayAttributeData HealthRegenRate;
	ATTRIBUTE_ACCESSORS(UDRSCharacterAttributeSet, HealthRegenRate)

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UDRSCharacterAttributeSet, Mana)
	
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Attributes")
	FGameplayAttributeData ManaRegenRate;
	ATTRIBUTE_ACCESSORS(UDRSCharacterAttributeSet, ManaRegenRate)
};
