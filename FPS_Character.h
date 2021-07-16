// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FPS_Bullet.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/DecalComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DrawDebugHelpers.h"
#include "FPS_Enemy.h"
#include "FloatingActor.h"
#include "ShiftDoor.h"
#include "InGameButton.h"
#include "FPS_PlayerController.h"
#include "Scope.h"
#include "Weapon.h"
#include "FPS_Character.generated.h"

UCLASS()
class FPS_TEST_API AFPS_Character : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPS_Character();	
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
		TSubclassOf<class AFPS_Bullet> BulletClass;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual bool CanJumpInternal_Implementation() const override;
	virtual void AddControllerPitchInput(float Val);
	virtual void AddControllerYawInput(float Val) ;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		USkeletalMeshComponent* FPS_Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* Character_Mesh;
	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* Gun_Mesh;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		USkeletalMeshComponent* CharacterGun_Mesh;

	UPROPERTY(EditAnywhere)
		UCameraComponent*  FPS_Camera;
	UPROPERTY(EditAnywhere)
		TSubclassOf<AScope> FPS_Scope;

	UPROPERTY(EditDefaultsOnly, Category = Emitter)
		UParticleSystem* HitEmitter;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;

	UPROPERTY(EditDefaultsOnly, Category = Audio)
		USoundBase* FPS_Grenade_Audio;
	UPROPERTY(EditDefaultsOnly, Category = Audio)
		USoundBase* FPS_CannotShoot_Audio;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TArray<AWeapon*> Weapons;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		AWeapon* WeaponNow;
	UPROPERTY(BlueprintReadWrite)
		bool InAim = false;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
		int32 Character_Health=100;
	UPROPERTY(EditDefaultsOnly, Category = Audio)
		USoundBase* FPS_Hit_Audio;
	UPROPERTY(EditDefaultsOnly, Category = Audio)
		USoundBase* FPS_KnifeLight_Audio;
	UPROPERTY(EditDefaultsOnly, Category = Audio)
		USoundBase* FPS_KnifeHeavy_Audio;

	UPROPERTY(EditAnywhere, Category = "BulletHole")
		FVector Bullet_Hole_Size;
	UPROPERTY(EditDefaultsOnly,Category = "BulletHole")
		UMaterialInterface* Bullet_Hole;
	UPROPERTY(EditDefaultsOnly, Category = "BulletHole")
		UMaterialInterface* Bullet_HoleLight;
	UPROPERTY(EditDefaultsOnly, Category = "Shake")
		TSubclassOf<UCameraShakeBase> FireCameraShake;
	UPROPERTY(EditDefaultsOnly, Category = "Shake")
		TSubclassOf<UCameraShakeBase> AimCameraShake;
	UPROPERTY(EditDefaultsOnly, Category = "Shake")
		TSubclassOf<UCameraShakeBase> MoveCameraShake;


	bool InReload=false;
	bool IsDead = false;

	FTimerHandle Dead_TimeHandle;
	FTimerHandle Fire_TimeHandle;
	FTimerHandle Reload_TimeHandle;
	AFPS_PlayerController* PC;
	FVector CameraLocation;
	FRotator CameraRotation;
	AScope* Scope;
	FHitResult Act{ ForceInit };

	UFUNCTION()
		void Move_Forward(float value);
	UFUNCTION()
		void Move_Right(float value);
	UFUNCTION()
		void Start_Jump();
	UFUNCTION()
		void Stop_Jump();
	UFUNCTION()
		void Fire();
	UFUNCTION()
		void Stop_Fire();
	UFUNCTION()
		void TiltLeft();
	UFUNCTION()
		void TiltRight();
	UFUNCTION()
		void AimorHeavyAttack();
	UFUNCTION()
		void Stop_Aim();
	UFUNCTION()
		void Run();
	UFUNCTION()
		void Stop_Run();
	UFUNCTION()
		virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	UFUNCTION()
		void Shoot();
	UFUNCTION()
		void KnifeAttack(bool Type);
	UFUNCTION()
		void ChangeWeapon(int i);
	UFUNCTION()
		void ChangeWeapon1();
	UFUNCTION()
		void ChangeWeapon2();
	UFUNCTION()
		void ChangeWeapon3();
	UFUNCTION()
		void Reload();
	UFUNCTION()
		void StartReload();
	UFUNCTION()
		void Interact();
	UFUNCTION()
		void Grenade_Shoot();
	UFUNCTION()
		void PauseGame();
	UFUNCTION()
		void Dead();
};
