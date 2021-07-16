// Fill out your copyright notice in the Description page of Project Settings.


#include "Scope.h"

// Sets default values
AScope::AScope()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ScopeCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("ScopeCamera"));
	ScopeCamera->SetupAttachment(RootComponent);
	ScopeCamera->FieldOfView = 50;
	ScopeCamera->bUsePawnControlRotation = true;
}

// Called when the game starts or when spawned
void AScope::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AScope::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

