// Fill out your copyright notice in the Description page of Project Settings.


#include "Elevator.h"

// Sets default values
AElevator::AElevator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	Elevator_Mesh= CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ElevatorMesh"));
	Elevator_Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	Door_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
	Door_Mesh->AttachToComponent(Elevator_Mesh, FAttachmentTransformRules::KeepRelativeTransform);
	CharacterInElevator = CreateDefaultSubobject<UBoxComponent>(TEXT("CharacterIn"));
	CharacterInElevator->AttachToComponent(Elevator_Mesh, FAttachmentTransformRules::KeepRelativeTransform);
	DoorTimeLineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("DoorTimeLine"));
	ElevatorTimeLineComp = CreateDefaultSubobject<UTimelineComponent>(TEXT("ElevatorTimeLine"));
	UpdateOpenDoor.BindUFunction(this, FName{ TEXT("OpenDoor") });
}
// Called when the game starts or when spawned
void AElevator::BeginPlay()
{
	Super::BeginPlay();
	CharacterInElevator->OnComponentBeginOverlap.AddDynamic(this, &AElevator::CharacterInOverLap);
	CharacterInElevator->OnComponentEndOverlap.AddDynamic(this, &AElevator::CharacterOutOverLap);
	UpdateDoorFunctionFloat.BindDynamic(this, &AElevator::TimeLineDoor);
	UpdateElevatorFunctionFloat.BindDynamic(this, &AElevator::TimeLineElevator);
	if (DoorTimeLineCurve)
	{
		DoorTimeLineComp->AddInterpFloat(DoorTimeLineCurve, UpdateDoorFunctionFloat);
	}
	if (ElevatorTimeLineCurve)
	{
		ElevatorTimeLineComp->AddInterpFloat(ElevatorTimeLineCurve, UpdateElevatorFunctionFloat);
	}
}

// Called every frame
void AElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AElevator::TimeLineDoor(float Update)
{
	FVector NowLocation = Door_Mesh->GetRelativeLocation();
	Door_Mesh->SetRelativeLocation(FVector(NowLocation.X, Update, NowLocation.Z));
}
void AElevator::TimeLineElevator(float Update)
{
	FVector NowLocation = RootComponent->GetRelativeLocation();
	RootComponent->SetRelativeLocation(FVector(NowLocation.X, NowLocation.Y, Update));
}
void AElevator::CharacterInOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass()->IsChildOf(AFPS_Character::StaticClass()))
	{
		if (Open == false)
		{
			DoorTimeLineComp->Play();
			Open = true;
		}
	}
}
void AElevator::CharacterOutOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
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
void AElevator::PressUp()
{
	if (NowFloor < MaxFloor)
	{
		DoorTimeLineComp->Reverse();
		ElevatorTimeLineComp->Play();
		ElevatorTimeLineComp->SetTimelineFinishedFunc(UpdateOpenDoor);
		NowFloor++;
	}
}
void AElevator::PressDown()
{
	if (NowFloor > 1)
	{
		DoorTimeLineComp->Reverse();
		ElevatorTimeLineComp->Reverse();
		ElevatorTimeLineComp->SetTimelineFinishedFunc(UpdateOpenDoor);
		NowFloor--;
	}
}
void AElevator::OpenDoor()
{
	DoorTimeLineComp->Play();
	Open = true;
}