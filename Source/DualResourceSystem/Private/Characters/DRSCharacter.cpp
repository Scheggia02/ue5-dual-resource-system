// Fill out your copyright notice in the Description page of Project Settings.


#include "Characters/DRSCharacter.h"
#include "Components/DRSResourceExecutionComponent.h"

// Sets default values
ADRSCharacter::ADRSCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
	
	ResourceExecutionComponent = CreateDefaultSubobject<UDRSResourceExecutionComponent>(TEXT("ResourceExecutionComponent"));
}

void ADRSCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ADRSCharacter::Tick(const float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADRSCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Internal check in the base class to ensure PlayerInputComponent is valid before binding any input.
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

