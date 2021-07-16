// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include"Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "GameOverWidget.generated.h"

/**
 * 
 */
UCLASS()
class FPS_TEST_API UGameOverWidget : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(meta = (BindWidget))
	UButton* RestartButton;
	UPROPERTY(meta = (BindWidget))
	UButton* BacktoMainButton;
public:
	UFUNCTION()
	void RestartGame();
	UFUNCTION()
	void BacktoMain();
	UFUNCTION()
	virtual bool Initialize();
};
