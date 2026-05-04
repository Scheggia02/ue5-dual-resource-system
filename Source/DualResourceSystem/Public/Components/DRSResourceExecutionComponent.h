// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DRSResourceExecutionComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class DUALRESOURCESYSTEM_API UDRSResourceExecutionComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UDRSResourceExecutionComponent();

	virtual void BeginPlay() override;
};
