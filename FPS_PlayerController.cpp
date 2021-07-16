// Fill out your copyright notice in the Description page of Project Settings.


#include "FPS_PlayerController.h"
#include "Blueprint\UserWidget.h"
void AFPS_PlayerController::BeginPlay()
{
	Super::BeginPlay();
}
void AFPS_PlayerController::GameStart()
{
	SetInputMode(FInputModeGameOnly{});
	bShowMouseCursor = false;
	if (IngameHUDAsset)
	{
		IngameHUD = CreateWidget<UUserWidget>(this, IngameHUDAsset);
	}
	if (IngameHUD)
	{
		IngameHUD->AddToViewport();
	}
}
void AFPS_PlayerController::PauseGame()
{
	SetInputMode(FInputModeUIOnly{});
	bShowMouseCursor = true;
	if (PauseHUDAsset)
	{
		PauseHUD = CreateWidget<UUserWidget>(this, PauseHUDAsset);
	}
	if (PauseHUD)
	{
		PauseHUD->AddToViewport();
	}
}
void AFPS_PlayerController::UnPauseGame()
{
	SetInputMode(FInputModeGameOnly{}); 
	bShowMouseCursor = false;
	if (PauseHUD)
	{
		PauseHUD->RemoveFromViewport();
	}
}
void AFPS_PlayerController::PCDead()
{
	if (IngameHUD)
	{
		IngameHUD->RemoveFromViewport();
	}
	if (DeadHUDAsset)
	{
		DeadHUD = CreateWidget<UUserWidget>(this, DeadHUDAsset);
		bShowMouseCursor = true;
		SetInputMode(FInputModeUIOnly{});
	}
	if (DeadHUD)
	{
		DeadHUD->AddToViewport();
	}
}
void AFPS_PlayerController::Victory()
{
	if (IngameHUD)
	{
		IngameHUD->RemoveFromViewport();
	}
	if (WinHUDAsset)
	{
		WinHUD = CreateWidget<UUserWidget>(this, WinHUDAsset);
		bShowMouseCursor = true;
		SetInputMode(FInputModeUIOnly{});
	}
	if (WinHUD)
	{
		WinHUD->AddToViewport();
	}
	UGameplayStatics::SetGamePaused(this->GetWorld(), true);
}