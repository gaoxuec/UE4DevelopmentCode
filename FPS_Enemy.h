// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FPS_AIController.h"
#include "Perception/PawnSensingComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "FPS_Character.h"
#include "FPS_Enemy.generated.h"

UCLASS()
class FPS_TEST_API AFPS_Enemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AFPS_Enemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent* Enemy_Mesh;
	UPROPERTY(EditAnywhere, Category = Sight)
		UPawnSensingComponent* Enemy_Sight;
	UPROPERTY(EditAnywhere)
		int32 Enemy_Health;
	UPROPERTY(EditAnywhere)
		int32 Enemy_Damage;
	UPROPERTY(EditAnywhere, Category = Montage)
		class UAnimMontage* AIAttack;
	UAnimInstance* AIAnim;
	UBlackboardComponent* FPS_CharacterData;
	FTimerHandle TimeHandle;
	UFUNCTION()
		void HaveSeenPawn(APawn* Pawn);
	UFUNCTION()
		void Attack();
	void Enemy_Dead();
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
