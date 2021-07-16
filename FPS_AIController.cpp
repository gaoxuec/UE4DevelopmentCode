// Fill out your copyright notice in the Description page of Project Settings.


#include "FPS_AIController.h"

AFPS_AIController::AFPS_AIController()
{
    BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTree"));
}
void AFPS_AIController::OnPossess(APawn* InPawn)
{
    AFPS_Enemy* Enemy = Cast<AFPS_Enemy>(InPawn);
    if (Enemy == nullptr) return;	
    Super::OnPossess(InPawn);
    if (BehaviorTreeComp != nullptr)
    {
        if (BehaviorTree != nullptr)
        {
            BehaviorTreeComp->StartTree(*BehaviorTree);
            Enemy->FPS_CharacterData->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
        }
        RunBehaviorTree(BehaviorTree);
    }
}
void AFPS_AIController::OnUnPossess()
{
    Super::OnUnPossess();
    if (BehaviorTreeComp != nullptr)
    {
        BehaviorTreeComp->StopTree(EBTStopMode::Safe);
        SetPawn(NULL);
    }
}
