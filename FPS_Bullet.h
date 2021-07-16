// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include"Components/SphereComponent.h"
#include"GameFrameWork/ProjectileMovementComponent.h"
#include"Particles/ParticleSystemComponent.h"
#include"Kismet/GameplayStatics.h"
#include "FPS_Bullet.generated.h"

UCLASS()
class FPS_TEST_API AFPS_Bullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFPS_Bullet();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		USphereComponent* CollisionComponent;
	UPROPERTY(VisibleAnywhere,Category=Movement)
		UProjectileMovementComponent* ProjectileMovement;
	UPROPERTY(EditAnywhere, Category = Projectile)
		UStaticMeshComponent* Bullet_Mesh;
	UPROPERTY(EditAnywhere, Category = Movement)
		UMaterialInstanceDynamic* Bullet_Material;
	UFUNCTION()
		void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	UFUNCTION()
		void OnOverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void FireDirection(const FVector& ShootDirection);
	UPROPERTY(EditDefaultsOnly,Category=Emitter)
		UParticleSystem* HitEmitter;
	UPROPERTY(EditDefaultsOnly, Category = Emitter)
		UParticleSystemComponent* BulletEmitter;
	UPROPERTY(EditDefaultsOnly, Category = Audio)
		USoundBase* FPS_Hit_Audio;
};
