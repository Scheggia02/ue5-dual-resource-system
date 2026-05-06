// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DRSResourceExecutionComponent.generated.h"


/**
 * Actor component reserved for executing resource-related gameplay behavior.
 *
 * The component is attached to DRS characters as an extension point for resource spending,
 * regeneration, or other resource execution rules. It currently performs no per-frame ticking.
 */
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUALRESOURCESYSTEM_API UDRSResourceExecutionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	/** Creates the component and disables ticking by default. */
	UDRSResourceExecutionComponent();

	/** Standard component begin-play hook. */
	virtual void BeginPlay() override;
};
