// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "FPS_TestGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class FPS_TEST_API AFPS_TestGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
		virtual void StartPlay() override;
};
