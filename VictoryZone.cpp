// Fill out your copyright notice in the Description page of Project Settings.


#include "VictoryZone.h"


// Sets default values
AVictoryZone::AVictoryZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	VictoryZone = CreateDefaultSubobject<UBoxComponent>(TEXT("VictoryZone"));
	ZoneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	this->RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	VictoryZone->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepRelativeTransform);
	ZoneMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AVictoryZone::BeginPlay()
{
	Super::BeginPlay();
	VictoryZone->OnComponentBeginOverlap.AddDynamic(this, &AVictoryZone::CharacterInOverLap);
}

// Called every frame
void AVictoryZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AVictoryZone::CharacterInOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass()->IsChildOf(AFPS_Character::StaticClass()))
	{
		AFPS_Character* Character = Cast<AFPS_Character>(OtherActor);
		AFPS_PlayerController* PC = Cast<AFPS_PlayerController>(Character->GetController());
		if (PC->ProjectileCount > 10)
		{
			PC->Victory();
		}
	}
}