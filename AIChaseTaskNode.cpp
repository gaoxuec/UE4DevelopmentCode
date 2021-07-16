// Fill out your copyright notice in the Description page of Project Settings.


#include "AIChaseTaskNode.h"

EBTNodeResult::Type UAIChaseTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    AFPS_AIController* AIController = Cast<AFPS_AIController>(OwnerComp.GetAIOwner());
    if (AIController)
    {
        FVector TargetLocation = OwnerComp.GetBlackboardComponent()->GetValueAsVector(TEXT("TargetLocation"));
        AFPS_Enemy* AI = Cast<AFPS_Enemy>(AIController->GetPawn());
        if (AI)
        {
            FVector EnemyLocation = Cast<AFPS_Enemy>(AIController->GetPawn())->GetActorLocation();
            AFPS_Character* Player = Cast<AFPS_Character>(GetWorld()->GetFirstPlayerController()->GetPawn());
            FVector PlayerLocation = Player->GetActorLocation();
            float Distance = (PlayerLocation - EnemyLocation).Size();
            AIController->MoveToLocation(TargetLocation);
            return EBTNodeResult::Succeeded;
        }
        else
        {
            return EBTNodeResult::Failed;
        }
    }
    else
    {
        return EBTNodeResult::Failed;
    }
}