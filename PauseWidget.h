// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "FPS_PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "PauseWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPS_TEST_API UPauseWidget : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(meta = (BindWidget))
		UButton* BackButton;
	UPROPERTY(meta = (BindWidget))
		UButton* BacktoMainButton;
	UPROPERTY(meta = (BindWidget))
		UButton* ExitButton;
public:
	UFUNCTION()
		void BacktoGame();
	UFUNCTION()
		void BacktoMain();
	UFUNCTION()
		void ExitGame();
	UFUNCTION()
		virtual bool Initialize();
};
