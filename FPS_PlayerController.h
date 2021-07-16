// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "FPS_PlayerController.generated.h"

/**
 * 
 */
UCLASS()
class FPS_TEST_API AFPS_PlayerController : public APlayerController
{
	GENERATED_BODY()
	virtual void BeginPlay();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UUserWidget> IngameHUDAsset;
	class UUserWidget* IngameHUD;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UUserWidget> PauseHUDAsset;
	class UUserWidget* PauseHUD;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UUserWidget> DeadHUDAsset;
	class UUserWidget* DeadHUD;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UUserWidget> WinHUDAsset;
	class UUserWidget* WinHUD;
	UPROPERTY(BlueprintReadWrite)
		int32 ProjectileCount;
	UFUNCTION()
		void PCDead();
	UFUNCTION()
		void PauseGame();
	UFUNCTION()
		void UnPauseGame();
	UFUNCTION()
		void GameStart();
	UFUNCTION()
		void Victory();
};
