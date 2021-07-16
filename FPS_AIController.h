// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "FPS_Enemy.h"
#include"FPS_Character.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "FPS_AIController.generated.h"

/**
 * 
 */
UCLASS()
class FPS_TEST_API AFPS_AIController : public AAIController
{
	GENERATED_BODY()
	UBehaviorTreeComponent* BehaviorTreeComp;
	UPROPERTY(EditAnyWhere)
	UBehaviorTree* BehaviorTree;
public:
	FORCEINLINE UBehaviorTreeComponent* GetBehaviorTreeCompo() { return BehaviorTreeComp; }
	AFPS_AIController();
	virtual void OnPossess(APawn* InPawn);
	virtual void OnUnPossess();
};
