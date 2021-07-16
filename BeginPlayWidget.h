// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "BeginPlayWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPS_TEST_API UBeginPlayWidget : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(meta = (BindWidget))
		UButton* StartButton;
	UPROPERTY(meta = (BindWidget))
		UButton* ExitButton;
public:
	UFUNCTION()
		void StartGame();
	UFUNCTION()
		void ExitGame();
	UFUNCTION()
		virtual bool Initialize();
};
