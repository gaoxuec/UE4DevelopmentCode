// Fill out your copyright notice in the Description page of Project Settings.


#include "Shell.h"

// Sets default values
AShell::AShell()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent= CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	Shell_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Shell_Mesh"));
	Shell_Mesh->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);
	if (!ProjectileMovement)
	{
		ProjectileMovement = CreateDefaultSubobject < UProjectileMovementComponent >(TEXT("ProjectileMovement"));
		ProjectileMovement->SetUpdatedComponent(Shell_Mesh);
		ProjectileMovement->InitialSpeed = 800.0f;
		ProjectileMovement->bRotationFollowsVelocity = true;
		ProjectileMovement->bShouldBounce = true;
		ProjectileMovement->Bounciness = 0.2f;
		ProjectileMovement->ProjectileGravityScale = 1.0f;
	}
	InitialLifeSpan = 5.0f;
}

// Called when the game starts or when spawned
void AShell::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AShell::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

