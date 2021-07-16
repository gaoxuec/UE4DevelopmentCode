// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Engine/Canvas.h" 
#include "FPS_HUD.generated.h"

/**
 * 
 */
UCLASS()
class FPS_TEST_API AFPS_HUD : public AHUD
{
	GENERATED_BODY()
public:
	UPROPERTY(EditDefaultsOnly)
		UTexture2D* CrossHairTexture;
	virtual void DrawHUD() override;
};
