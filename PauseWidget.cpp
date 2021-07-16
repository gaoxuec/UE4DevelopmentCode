// Fill out your copyright notice in the Description page of Project Settings.


#include "PauseWidget.h"

bool UPauseWidget::Initialize()
{
    Super::Initialize();
    if (BackButton)
    {
        BackButton->OnClicked.AddDynamic(this, &UPauseWidget::BacktoGame);
    }
    if (BacktoMainButton)
    {
        BacktoMainButton->OnClicked.AddDynamic(this, &UPauseWidget::BacktoMain);
    }
    if (ExitButton)
    {
        ExitButton->OnClicked.AddDynamic(this, &UPauseWidget::ExitGame);
    }
    return true;
}
void UPauseWidget::BacktoGame()
{
    UGameplayStatics::SetGamePaused(this->GetWorld(), false);
    AFPS_PlayerController* PlayerController = Cast<AFPS_PlayerController>(UGameplayStatics::GetPlayerController(this, 0));
    PlayerController->UnPauseGame();
}
void UPauseWidget::BacktoMain()
{
    UGameplayStatics::OpenLevel(GetWorld(), TEXT("FPS_Begin"));
}
void UPauseWidget::ExitGame()
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    UKismetSystemLibrary::QuitGame(this, PlayerController, EQuitPreference::Quit, true);
}
