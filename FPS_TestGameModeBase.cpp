// Copyright Epic Games, Inc. All Rights Reserved.


#include "FPS_TestGameModeBase.h"
#include"Engine/Engine.h"

void AFPS_TestGameModeBase::StartPlay()
{
    Super::StartPlay();
    check(GEngine);
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, TEXT("Hello World, this is FPSGameMode!"));

}