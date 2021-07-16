// Fill out your copyright notice in the Description page of Project Settings.


#include "CloseBTDecorator.h"
bool UCloseBTDecorator::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
    AFPS_AIController* AIController = Cast<AFPS_AIController>(OwnerComp.GetAIOwner());
    if (AIController)
    {
        FVector EnemyLocation = Cast<AFPS_Enemy>(AIController->GetPawn())->GetActorLocation();
        AFPS_Character* Player = Cast<AFPS_Character>(GetWorld()->GetFirstPlayerController()->GetPawn());
        if (Player)
        {
            FVector PlayerLocation = Player->GetActorLocation();
            float Distance = (PlayerLocation - EnemyLocation).Size(); 
            if (Distance < FDistance)
            {
                AIController->StopMovement();
                return false;
            }
            else
            {
                return true;
            }
        }
        else
        {
            return false;
        }
    }
    else
    {
        return false;
    }
}

