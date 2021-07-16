// Fill out your copyright notice in the Description page of Project Settings.


#include "FPS_Bullet.h"

// Sets default values
AFPS_Bullet::AFPS_Bullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionComponent"));
	CollisionComponent->InitSphereRadius(5.0f);	
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	CollisionComponent->OnComponentHit.AddDynamic(this, &AFPS_Bullet::OnHit);
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AFPS_Bullet::OnOverLap);
	RootComponent = CollisionComponent;
	if (!ProjectileMovement)
	{
		ProjectileMovement = CreateDefaultSubobject < UProjectileMovementComponent >(TEXT("ProjectileMovement"));
		ProjectileMovement->SetUpdatedComponent(CollisionComponent);
		ProjectileMovement->InitialSpeed = 3000.0f;
		ProjectileMovement->MaxSpeed = 3000.0f;
		ProjectileMovement->bRotationFollowsVelocity = true;
		ProjectileMovement->bShouldBounce = true;
		ProjectileMovement->Bounciness = 0.5f;
		ProjectileMovement->ProjectileGravityScale = 1.0f;
	}
	Bullet_Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet_Mesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>Mesh(TEXT("StaticMesh'/Game/Sources/OldSources/Sphere_2.Sphere_2'"));
	if (Mesh.Succeeded())
	{
		Bullet_Mesh->SetStaticMesh(Mesh.Object);
	}
	Bullet_Material = CreateDefaultSubobject<UMaterialInstanceDynamic>(TEXT("Bullet_Material"));
	static ConstructorHelpers::FObjectFinder<UMaterial>Material(TEXT("Material'/Game/Sources/OldSources/NewMaterial.NewMaterial'"));
	Bullet_Material = UMaterialInstanceDynamic::Create(Material.Object, Bullet_Mesh);
	Bullet_Mesh->SetMaterial(0, Bullet_Material);
	Bullet_Mesh->SetRelativeScale3D(FVector(0.09f, 0.09f, 0.09f));
	Bullet_Mesh->SetupAttachment(RootComponent);
	BulletEmitter = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("BulletEmitter"));
	BulletEmitter->SetupAttachment(Bullet_Mesh);
	InitialLifeSpan = 3.0f;
}

// Called when the game starts or when spawned
void AFPS_Bullet::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AFPS_Bullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
void AFPS_Bullet::FireDirection(const FVector& ShootDirection)
{
	ProjectileMovement->Velocity = ShootDirection * ProjectileMovement->InitialSpeed;
}
void AFPS_Bullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this && OtherComponent->IsSimulatingPhysics())
	{
		OtherComponent->AddImpulseAtLocation(ProjectileMovement->Velocity * 100.0f, Hit.ImpactPoint);
	}
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEmitter, this->GetTransform());
	UGameplayStatics::PlaySound2D(GetWorld(), FPS_Hit_Audio);
	Destroy();
}
void AFPS_Bullet::OnOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor != this)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEmitter, this->GetTransform());
		UGameplayStatics::PlaySound2D(GetWorld(), FPS_Hit_Audio);
		Destroy();
	}
}