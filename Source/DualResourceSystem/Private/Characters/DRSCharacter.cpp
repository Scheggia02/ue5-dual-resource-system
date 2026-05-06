// Fill out your copyright notice in the Description page of Project Settings.

#include "Characters/DRSCharacter.h"

#include "Attributes/DRSCharacterAttributeSet.h"
#include "Components/DRSAbilitySystemComponent.h"
#include "Components/DRSResourceExecutionComponent.h"
#include "Data/DRSCharacterConfigData.h"
#include "Engine/AssetManager.h"

ADRSCharacter::ADRSCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	
	// These attribute sets will be detected by AbilitySystemComponent::InitializeComponent. Keeping a reference so that the sets don't get garbage collected before that.
	AttributeSet = CreateDefaultSubobject<UDRSCharacterAttributeSet>(TEXT("AttributeSet"));
	
	AbilitySystemComponent = CreateDefaultSubobject<UDRSAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	ResourceExecutionComponent = CreateDefaultSubobject<UDRSResourceExecutionComponent>(TEXT("ResourceExecutionComponent"));
}

void ADRSCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ADRSCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	LoadCharacterConfigData();
}

void ADRSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Internal check in the base class to ensure PlayerInputComponent is valid before binding any input.
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ADRSCharacter::LoadCharacterConfigData()
{
	checkf(CharacterConfigDataId.IsValid(), TEXT("CharacterConfigDataId is not valid on %s"), *GetName());	
	
	UAssetManager& AssetManager = UAssetManager::Get();
	AssetManager.LoadPrimaryAsset(CharacterConfigDataId, {}, FStreamableDelegate::CreateUObject(this, &ADRSCharacter::ApplyCharacterConfigData));
}

void ADRSCharacter::ApplyCharacterConfigData()
{
	checkf(CharacterConfigDataId.IsValid(), TEXT("CharacterConfigDataId is not valid on %s"), *GetName());

	const UAssetManager& AssetManager = UAssetManager::Get();
	CharacterConfigData = Cast<UDRSCharacterConfigData>(AssetManager.GetPrimaryAssetObject(CharacterConfigDataId));
	checkf(IsValid(CharacterConfigData), TEXT("Failed to load CharacterConfigData for %s"), *GetName());

	InitializeAbilitySystem();
}

void ADRSCharacter::InitializeAbilitySystem()
{
	checkf(IsValid(AbilitySystemComponent), TEXT("AbilitySystemComponent is not valid on %s"), *GetName());
	AbilitySystemComponent->InitAbilityActorInfo(this, this);

	if (!IsValid(CharacterConfigData))
	{
		return;
	}
	
	// Grant default abilities.
	AbilitySystemComponent->GrantAbilitiesById(CharacterConfigData->GetDefaultAbilities());
	
	// Initialize default attribute values.
	AbilitySystemComponent->ApplyAttributeSetEffect(CharacterConfigData->GetDefaultAttributeSetEffect());
}

