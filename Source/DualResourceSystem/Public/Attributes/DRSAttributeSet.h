// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "DRSAttributeSet.generated.h"

struct FGameplayEffectSpec;

/**
 * Defines the standard Gameplay Ability System accessor functions for an attribute property.
 *
 * Use this macro directly after declaring an FGameplayAttributeData UPROPERTY in an attribute set.
 * The generated helpers are used by Gameplay Effects, UI code, and gameplay systems that need a
 * typed way to read, write, initialize, or reference the attribute.
 *
 * The following example of the macro:
 *		ATTRIBUTE_ACCESSORS(UHealthSet, Health)
 * will create the following functions:
 *		static FGameplayAttribute GetHealthAttribute();
 *		float GetHealth() const;
 *		void SetHealth(float NewVal);
 *		void InitHealth(float NewVal);
 */
#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

 /**
  * Delegate signature for broadcasting attribute change events from DRS attribute sets.
  *
  * Some parameters may be null on clients depending on prediction, replication, and Gameplay Effect context.
  * This header only declares the delegate type; derived attribute sets decide when to broadcast it.
  *
  * @param EffectInstigator	The original instigating actor for this event
  * @param EffectCauser		The physical actor that caused the change
  * @param EffectSpec		The full effect spec for this change
  * @param EffectMagnitude	The raw magnitude, this is before clamping
  * @param OldValue			The value of the attribute before it was changed
  * @param NewValue			The value after it was changed
 */
DECLARE_MULTICAST_DELEGATE_SixParams(FDRSAttributeEvent, AActor* /*EffectInstigator*/, AActor* /*EffectCauser*/, const FGameplayEffectSpec* /*EffectSpec*/, float /*EffectMagnitude*/, float /*OldValue*/, float /*NewValue*/);

/**
 * Base class for Dual Resource System attribute sets.
 *
 * This class centralizes shared GAS attribute-set utilities, types, and future common behavior.
 * Concrete attribute sets, such as UDRSCharacterAttributeSet, inherit from this class to define
 * actual gameplay attributes like health, mana, regeneration rates, or other resources.
 */
UCLASS()
class DUALRESOURCESYSTEM_API UDRSAttributeSet : public UAttributeSet
{
 GENERATED_BODY()

public:

 UDRSAttributeSet();
};