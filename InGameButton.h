// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include"Elevator.h"
#include"Kismet/GameplayStatics.h"
#include "InGameButton.generated.h"

UCLASS()
class FPS_TEST_API AInGameButton : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AInGameButton();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent* Button_Mesh;
	UPROPERTY(EditAnywhere)
		int32 InteractWay;
	UPROPERTY(EditAnywhere)
		FString SurchName;
	UPROPERTY(EditAnywhere)
		TArray<AActor*> Actors;
	UFUNCTION()
		void Interact();
};
