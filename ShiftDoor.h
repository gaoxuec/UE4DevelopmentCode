// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/TimelineComponent.h"
#include "Components\BoxComponent.h"
#include"FPS_Character.h"
#include "ShiftDoor.generated.h"

UCLASS()
class FPS_TEST_API AShiftDoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShiftDoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent *Door_Mesh;
	UPROPERTY(EditAnywhere)
		UBoxComponent* CharacterIn;
	UPROPERTY(EditAnywhere, BluePrintReadWrite)
		UTimelineComponent* DoorTimeLineComp;
	UPROPERTY(EditAnywhere)
		UCurveFloat* DoorTimeLineCurve;
	FOnTimelineFloat UpdateFunctionFloat;
	UFUNCTION()
		void TimeLineMove(float Update);
	UFUNCTION()
		void Shift();
	UFUNCTION()
		void EndOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
	bool Open=false;
};
