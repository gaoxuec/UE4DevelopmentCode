// Fill out your copyright notice in the Description page of Project Settings.


#include "AIAttackBTTaskNode.h"

EBTNodeResult::Type UAIAttackBTTaskNode::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
            if (Distance < 200)
            {
                FVector StartLocation = AI->GetActorLocation();
                FVector EndLocation = StartLocation + AI->GetActorForwardVector() * 150;
                FHitResult Hit{ ForceInit };
                FCollisionQueryParams Params;
                Params.bTraceComplex = true;
                Params.bReturnPhysicalMaterial = false;
                Params.AddIgnoredActor(AI);
                GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_GameTraceChannel1, Params); 
                AI->Attack();
                if (Hit.GetActor())
                {
                    if (Hit.GetActor()->GetClass()->IsChildOf(AFPS_Character::StaticClass()))
                    {
                        UGameplayStatics::ApplyDamage(Hit.GetActor(), AI->Enemy_Damage, nullptr, AI, UDamageType::StaticClass());
                    }
                }
                return EBTNodeResult::Failed;
            }
            else
            {
                EBTNodeResult::Failed;
            }
        }
        else
        {
            return EBTNodeResult::Failed;
        }
    }
    return EBTNodeResult::Failed;
}
