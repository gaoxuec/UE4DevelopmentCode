// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/TimelineComponent.h"
#include "Components\BoxComponent.h"
#include"FPS_Character.h"
#include "Elevator.generated.h"

UCLASS()
class FPS_TEST_API AElevator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElevator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Elevator_Mesh;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Door_Mesh;
	UPROPERTY(EditAnywhere)
		UBoxComponent* CharacterInElevator;
	UPROPERTY(EditAnywhere, BluePrintReadWrite)
		UTimelineComponent* ElevatorTimeLineComp;
	UPROPERTY(EditAnywhere)
		UCurveFloat* ElevatorTimeLineCurve;
	UPROPERTY(EditAnywhere, BluePrintReadWrite)
		UTimelineComponent* DoorTimeLineComp;
	UPROPERTY(EditAnywhere)
		UCurveFloat* DoorTimeLineCurve;
	UPROPERTY(EditAnywhere)
		int32 MaxFloor;
	FOnTimelineFloat UpdateElevatorFunctionFloat;
	FOnTimelineFloat UpdateDoorFunctionFloat;
	FOnTimelineEventStatic UpdateOpenDoor;
	bool Open = false;
	int32 NowFloor=1;
	UFUNCTION()
		void TimeLineElevator(float Update);
	UFUNCTION()
		void TimeLineDoor(float Update);
	UFUNCTION()
		void PressUp();
	UFUNCTION()
		void PressDown();
	UFUNCTION()
		void CharacterInOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
		void CharacterOutOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	UFUNCTION()
		void OpenDoor();
};
