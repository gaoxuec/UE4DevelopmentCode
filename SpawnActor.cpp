// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnActor.h"

// Sets default values
ASpawnActor::ASpawnActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ASpawnActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UWorld* World=GetWorld();
	RunningTime -= DeltaTime;
	if (World)
	{
		if (RunningTime < 0.0f)
		{
			RunningTime += BetweenTime;
			FVector SpawnLocation = GetActorLocation();
			FRotator SpawnRotation = GetActorRotation();
			FActorSpawnParameters Param;
			Param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButDontSpawnIfColliding;
			World->SpawnActor<AFloatingActor>(FloatingActorClass,SpawnLocation,SpawnRotation,Param);
		}
		
	}
}

