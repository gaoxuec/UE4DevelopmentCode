// Fill out your copyright notice in the Description page of Project Settings.


#include "ShiftDoor.h"

// Sets default values
AShiftDoor::AShiftDoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	Door_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	Door_Mesh->AttachToComponent(RootComponent,FAttachmentTransformRules::KeepWorldTransform);
	CharacterIn = CreateDefaultSubobject<UBoxComponent>(TEXT("CharacterIn"));
	CharacterIn->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	DoorTimeLineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("TimeLine"));
}

// Called when the game starts or when spawned
void AShiftDoor::BeginPlay()
{
	Super::BeginPlay();
	CharacterIn->OnComponentEndOverlap.AddDynamic(this, &AShiftDoor::EndOverLap);
	UpdateFunctionFloat.BindDynamic(this,&AShiftDoor::TimeLineMove);
	if (DoorTimeLineCurve)
	{
		DoorTimeLineComp->AddInterpFloat(DoorTimeLineCurve, UpdateFunctionFloat);
	}
}

// Called every frame
void AShiftDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AShiftDoor::TimeLineMove(float Update)
{
		FVector NowLocation = Door_Mesh->GetRelativeLocation();
		Door_Mesh->SetRelativeLocation(FVector(NowLocation.X,Update,NowLocation.Z));
}
void AShiftDoor::Shift()
{
	if (Open == false)
	{
		DoorTimeLineComp->Play();
		Open = true;
	}
}
void AShiftDoor::EndOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (OtherActor->GetClass()->IsChildOf(AFPS_Character::StaticClass()))
	{
		if (Open == true)
		{
			DoorTimeLineComp->Reverse();
			Open = false;
		}
	}
}