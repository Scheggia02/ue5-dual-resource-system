// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DRSHealthComponent.generated.h"


class UDRSAbilitySystemComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DUALRESOURCESYSTEM_API UDRSHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UDRSHealthComponent();

	UFUNCTION(BlueprintPure, Category = "Health")
	bool IsDeadOrDying() const;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetCurrentHealth() const;
	
private:
	UDRSAbilitySystemComponent* GetOwnerAbilitySystemComponent() const;
};
