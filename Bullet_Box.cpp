// Fill out your copyright notice in the Description page of Project Settings.


#include "Bullet_Box.h"

// Sets default values
ABullet_Box::ABullet_Box()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABullet_Box::OnOverLap);
	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	BoxMesh->SetupAttachment(CollisionBox);
}

// Called when the game starts or when spawned
void ABullet_Box::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet_Box::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet_Box::OnOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor->GetClass()->IsChildOf(AFPS_Character::StaticClass()))
	{
		AFPS_Character* Player = Cast<AFPS_Character>(OtherActor);
		Player->WeaponNow->Spare_Bullet_Number += Bullet_Number;
		this->Destroy();
	}
}