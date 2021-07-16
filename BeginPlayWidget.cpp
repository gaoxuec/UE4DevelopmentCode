// Fill out your copyright notice in the Description page of Project Settings.


#include "BeginPlayWidget.h"

bool UBeginPlayWidget::Initialize()
{
    Super::Initialize();
    if (StartButton)
    {
        StartButton->OnClicked.AddDynamic(this, &UBeginPlayWidget::StartGame);
    }
    if (ExitButton)
    {
        ExitButton->OnClicked.AddDynamic(this, &UBeginPlayWidget::ExitGame);
    }

    return true;
}
void UBeginPlayWidget::StartGame()
{
    this->RemoveFromViewport();   
    UGameplayStatics::OpenLevel(GetWorld(), TEXT("FPS_Map"));
}
void UBeginPlayWidget::ExitGame()
{
    APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
    UKismetSystemLibrary::QuitGame(this, PlayerController, EQuitPreference::Quit,true);
}