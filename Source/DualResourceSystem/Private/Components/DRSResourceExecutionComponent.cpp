// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/DRSResourceExecutionComponent.h"

// Sets default values for this component's properties
UDRSResourceExecutionComponent::UDRSResourceExecutionComponent()
{
	// No need to tick every frame for this component, so we disable ticking.
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}


void UDRSResourceExecutionComponent::BeginPlay()
{
	Super::BeginPlay();
}
