// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameButton.h"

// Sets default values
AInGameButton::AInGameButton()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	Button_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Button_Mesh"));
	Button_Mesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AInGameButton::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInGameButton::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}
void AInGameButton::Interact()
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AElevator::StaticClass(), Actors);
	for (AActor* Actor : Actors)
	{
		
		if (Actor->GetName() == SurchName)
		{
			if (InteractWay == 1)
			{
				Cast<AElevator>(Actor)->PressUp();
			}
			if(InteractWay==0)
			{
				Cast<AElevator>(Actor)->PressDown();
			}
		}
	}
}
