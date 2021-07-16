// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include"Components\BoxComponent.h"
#include"FPS_Character.h"
#include "Bullet_Box.generated.h"

UCLASS()
class FPS_TEST_API ABullet_Box : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet_Box();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
		UBoxComponent* CollisionBox;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* BoxMesh;
	UPROPERTY(EditAnywhere)
		int32 Bullet_Number;
	UFUNCTION()
		void OnOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
