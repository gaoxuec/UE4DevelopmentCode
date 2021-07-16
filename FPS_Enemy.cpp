// Fill out your copyright notice in the Description page of Project Settings.


#include "FPS_Enemy.h"

// Sets default values
AFPS_Enemy::AFPS_Enemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Enemy_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Enemy_Mesh"));
	ConstructorHelpers::FObjectFinder<USkeletalMesh>EnemyMesh(TEXT("SkeletalMesh'/Game/Sources/NewSources/SK_Mannequin.SK_Mannequin'"));
	if (EnemyMesh.Succeeded())
	{
		Enemy_Mesh->SetSkeletalMesh(EnemyMesh.Object);
	}
	Enemy_Mesh->SetupAttachment(RootComponent);
	Enemy_Health = 100;
	AIControllerClass = AFPS_AIController::StaticClass();
	FPS_CharacterData = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoard"));
	Enemy_Sight = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("Enemy_Sight"));

}

// Called when the game starts or when spawned
void AFPS_Enemy::BeginPlay()
{
	Super::BeginPlay();
	AIAnim = Enemy_Mesh->GetAnimInstance();
	if (Enemy_Sight)
	{
		Enemy_Sight->OnSeePawn.AddDynamic(this,&AFPS_Enemy::HaveSeenPawn);
	}
}

// Called every frame
void AFPS_Enemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
// Called to bind functionality to input
void AFPS_Enemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}
float AFPS_Enemy::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(1, 2.0f, FColor::Red, TEXT("Hit"));
	Enemy_Health -= Damage;
	if (Enemy_Health <= 0)
	{
		Enemy_Mesh->SetSimulatePhysics(true);
		this->GetCapsuleComponent()->DestroyComponent();
		DetachFromControllerPendingDestroy();
		Enemy_Health = 100;
		GetWorldTimerManager().UnPauseTimer(TimeHandle);
		GetWorldTimerManager().SetTimer(TimeHandle, this, &AFPS_Enemy::Enemy_Dead, 3.0f, false, 3.0f);
		PrimaryActorTick.bCanEverTick = false;
	}
	return 0.0f;
}
void AFPS_Enemy::Enemy_Dead()
{	
	this->Destroy();
}
void AFPS_Enemy::HaveSeenPawn(APawn* Pawn)
{
	AFPS_Character* Player = Cast<AFPS_Character>(Pawn);
	if (this->Enemy_Health > 0)
	{
		if (Player)
		{
			FVector PlayerLocation = Player->GetActorLocation();
			if (FPS_CharacterData)
			{
				FPS_CharacterData->SetValueAsVector(TEXT("TargetLocation"), PlayerLocation); 
			}
		}
	}
}
void AFPS_Enemy::Attack()
{
	if (AIAttack)
	{
		if (!AIAnim->IsAnyMontagePlaying())
		{
			AIAnim->Montage_Play(AIAttack, 1.0);
		}
	}
}

