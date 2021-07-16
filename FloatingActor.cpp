// Fill out your copyright notice in the Description page of Project Settings.


#include "FloatingActor.h"

// Sets default values
AFloatingActor::AFloatingActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ActorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ActorMesh"));
	ActorMesh->OnComponentHit.AddDynamic(this,&AFloatingActor::CheckActor);
}

// Called when the game starts or when spawned
void AFloatingActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFloatingActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator ActorRotation;
	FVector ActorLocation;
	RunningTime = GetGameTimeSinceCreation();
	ActorRotation = GetActorRotation();
	ActorLocation = GetActorLocation();
	ActorRotation.Yaw += FMath::Sin(RunningTime+DeltaTime);
	ActorLocation.Z += FMath::Sin(RunningTime+DeltaTime)*5.0f;
	SetActorRotation(ActorRotation);
	SetActorLocation(ActorLocation);

}
void AFloatingActor::CheckActor(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	this->Destroy();
}

