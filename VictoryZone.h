// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "FPS_Character.h"
#include "FPS_PlayerController.h"
#include "VictoryZone.generated.h"

UCLASS()
class FPS_TEST_API AVictoryZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AVictoryZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
		UBoxComponent* VictoryZone;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* ZoneMesh;
	UFUNCTION()
		void CharacterInOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
