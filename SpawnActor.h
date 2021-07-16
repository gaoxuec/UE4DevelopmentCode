// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include"FloatingActor.h"
#include "SpawnActor.generated.h"

UCLASS()
class FPS_TEST_API ASpawnActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditDefaultsOnly,Category="Projectile")
		TSubclassOf<AFloatingActor> FloatingActorClass;
	float RunningTime;
	float BetweenTime=4.0f;
};
