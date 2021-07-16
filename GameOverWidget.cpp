// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"

bool UGameOverWidget::Initialize()
{
    Super::Initialize();
    if (RestartButton)
    {
        RestartButton->OnClicked.AddDynamic(this, &UGameOverWidget::RestartGame);
    }
    if (BacktoMainButton)
    {
        BacktoMainButton->OnClicked.AddDynamic(this, &UGameOverWidget::BacktoMain);
    }
     return true;
}
void UGameOverWidget::RestartGame()
{
    UGameplayStatics::OpenLevel(GetWorld(), TEXT("FPS_Map"));
}
void UGameOverWidget::BacktoMain()
{
    UGameplayStatics::OpenLevel(GetWorld(), TEXT("FPS_Begin"));
}