// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "DRSPlayerController.generated.h"

/**
 * Player controller class for the Dual Resource System project.
 *
 * Currently acts as the project-specific controller type configured by game mode or Blueprints,
 * leaving room for shared DRS player-control behavior to be added later.
 */
UCLASS()
class DUALRESOURCESYSTEM_API ADRSPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	/** Creates the DRS player controller. */
	ADRSPlayerController();
};
