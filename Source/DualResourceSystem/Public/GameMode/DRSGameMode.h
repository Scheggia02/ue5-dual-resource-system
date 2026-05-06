// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DRSGameMode.generated.h"

/**
 * Base game mode class for maps that use the Dual Resource System gameplay framework.
 *
 * This class currently provides a project-specific type derived from AGameModeBase so default pawn,
 * controller, and rule configuration can be assigned in C++ or Blueprint.
 */
UCLASS()
class DUALRESOURCESYSTEM_API ADRSGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
};
