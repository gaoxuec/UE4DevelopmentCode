// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include"FPS_AIController.h"
#include"FPS_Enemy.h"
#include "CloseBTDecorator.generated.h"

/**
 * 
 */
UCLASS()
class FPS_TEST_API UCloseBTDecorator : public UBTDecorator
{
	GENERATED_BODY()
		virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const;
	UPROPERTY(EditAnyWhere)
		float FDistance;
};
