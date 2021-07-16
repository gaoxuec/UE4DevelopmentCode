// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include"FPS_AIController.h"
#include "AIAttackBTTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class FPS_TEST_API UAIAttackBTTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
		virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory);
};
