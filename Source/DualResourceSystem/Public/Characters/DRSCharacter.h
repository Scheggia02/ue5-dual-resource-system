// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DRSCharacter.generated.h"

class UDRSResourceExecutionComponent;

UCLASS()
class DUALRESOURCESYSTEM_API ADRSCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ADRSCharacter();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	TObjectPtr<UDRSResourceExecutionComponent> ResourceExecutionComponent;

public:	
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
