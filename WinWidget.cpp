// Fill out your copyright notice in the Description page of Project Settings.


#include "WinWidget.h"


bool UWinWidget::Initialize()
{
    Super::Initialize();
    if (RestartButton)
    {
        RestartButton->OnClicked.AddDynamic(this, &UWinWidget::RestartGame);
    }
    if (BacktoMainButton)
    {
        BacktoMainButton->OnClicked.AddDynamic(this, &UWinWidget::BacktoMain);
    }
    return true;
}
void UWinWidget::RestartGame()
{
    UGameplayStatics::OpenLevel(GetWorld(), TEXT("FPS_Map"));
}
void UWinWidget::BacktoMain()
{
    UGameplayStatics::OpenLevel(GetWorld(), TEXT("FPS_Begin"));
}