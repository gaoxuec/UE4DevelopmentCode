// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include"FPS_AIController.h"
#include "AIChaseTaskNode.generated.h"

/**
 * 
 */
UCLASS()
class FPS_TEST_API UAIChaseTaskNode : public UBTTaskNode
{
	GENERATED_BODY()
public:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
