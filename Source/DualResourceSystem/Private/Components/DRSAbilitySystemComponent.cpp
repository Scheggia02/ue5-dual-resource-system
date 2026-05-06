// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DRSAbilitySystemComponent.h"

#include "AbilitySystem/Abilities/DRSGameplayAbility.h"
#include "Data/DRSGameplayAbilityData.h"
#include "Engine/AssetManager.h"


UDRSAbilitySystemComponent::UDRSAbilitySystemComponent()
{
}

void UDRSAbilitySystemComponent::GrantAbilitiesById(const TArray<FPrimaryAssetId>& AbilitiesToGrant)
{
	if (AbilitiesToGrant.Num() == 0)
	{
		return;
	}
	
	// Load the ability assets first, then grant the abilities in the callback once the assets are loaded. 
	UAssetManager::Get().LoadPrimaryAssets(AbilitiesToGrant, TArray<FName>(), FStreamableDelegate::CreateUObject(this, &UDRSAbilitySystemComponent::OnAbilityPrimaryAssetsLoaded, AbilitiesToGrant));
}

void UDRSAbilitySystemComponent::GrantAbilitiesByAsset(const TArray<UDRSGameplayAbilityData*>& AbilitiesToGrant)
{
	for (const auto& AbilityAsset : AbilitiesToGrant)
	{
		checkf(AbilityAsset->IsValid(), TEXT("Ability asset entry is not valid in GrantAbilities."));

		GrantAbilityByAsset(AbilityAsset);
	}
}

void UDRSAbilitySystemComponent::GrantAbilityByAsset(const UDRSGameplayAbilityData* AbilityAssetToGrant)
{
	checkf(IsValid(AbilityAssetToGrant), TEXT("Ability class entry is null in GrantAbilityByAsset."));

	const TSubclassOf<UDRSGameplayAbility> LoadedAbilityClass = AbilityAssetToGrant->GetAbilityClass().LoadSynchronous();
	checkf(IsValid(LoadedAbilityClass), TEXT("Failed to load ability class %s in GrantAbilityByAsset."), *AbilityAssetToGrant->GetName());

	FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(LoadedAbilityClass, AbilityAssetToGrant->GetAbilityLevel());
	AbilitySpec.SourceObject = this;
	
	/* Here we define the ability trigger flow, we add the input tag from the ability asset to the DynamicSpecSourceTags of the ability spec.
	 * This allows us to trigger the ability from the input tag using the GameplayTag system. When an input is triggered, 
	 * we can find the abilities with matching input tags in their DynamicSpecSourceTags and trigger them. */
	AbilitySpec.GetDynamicSpecSourceTags().AddTag(AbilityAssetToGrant->GetAbilityInputTag());
	
	// Grant the ability
	GiveAbility(AbilitySpec);
}

void UDRSAbilitySystemComponent::NotifyAbilityInputTriggered(FGameplayTag InputTag)
{
	if (!InputTag.IsValid())
	{
		UE_LOG(LogTemp, Warning, TEXT("Invalid InputTag passed to NotifyAbilityInputTriggered."));
		return;
	}
	
	// Iterate through the currently granted abilities and try to activate any ability that has a matching input tag in its DynamicSpecSourceTags.
	for (const auto& AbilitySpec : GetActivatableAbilities())
	{
		if (IsValid(AbilitySpec.Ability) && AbilitySpec.GetDynamicSpecSourceTags().HasTagExact(InputTag))
		{
			TryActivateAbility(AbilitySpec.Handle);
		}
	}
}

void UDRSAbilitySystemComponent::ApplyAttributeSetEffect(TSoftClassPtr<UGameplayEffect> AttributeSetEffectClass)
{
	checkf(!AttributeSetEffectClass.IsNull(), TEXT("AttributeSetEffectClass is null in ApplyAttributeSetEffect."));

	const TSubclassOf<UGameplayEffect> LoadedEffectClass = AttributeSetEffectClass.LoadSynchronous();
	check(IsValid(LoadedEffectClass));
	
	FGameplayEffectContextHandle EffectContextHandle = MakeEffectContext();
	EffectContextHandle.AddSourceObject(this);
	
	// Default level for base attributes, we do not want to apply any level scaling here since these are just the base values.
	constexpr int32 DefaultAttributesLevel = 1;
	
	const FGameplayEffectSpecHandle NewSpec = MakeOutgoingSpec(LoadedEffectClass, DefaultAttributesLevel, EffectContextHandle);
	ApplyGameplayEffectSpecToSelf(*NewSpec.Data.Get());
}

void UDRSAbilitySystemComponent::OnAbilityPrimaryAssetsLoaded(TArray<FPrimaryAssetId> AbilitiesToGrant)
{
	for (const auto& AbilityId : AbilitiesToGrant)
	{
		const UDRSGameplayAbilityData* LoadedAbilityAsset = Cast<UDRSGameplayAbilityData>(UAssetManager::Get().GetPrimaryAssetObject(AbilityId));
		checkf(IsValid(LoadedAbilityAsset), TEXT("Failed to load ability asset %s in OnAbilityPrimaryAssetsLoaded."), *AbilityId.ToString());

		GrantAbilityByAsset(LoadedAbilityAsset);
	}
}
