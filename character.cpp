// Fill out your copyright notice in the Description page of Project Settings.


#include "FPS_Character.h"
#include "Blueprint\UserWidget.h"

// Sets default values
AFPS_Character::AFPS_Character()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	JumpMaxCount = 2;
	PrimaryActorTick.bCanEverTick = true;
	Character_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Character_Mesh"));
	Character_Mesh->SetupAttachment(RootComponent);
	Character_Mesh->bOwnerNoSee = true;

	CharacterGun_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterGun_Mesh"));
	CharacterGun_Mesh->SetupAttachment(Character_Mesh);
	CharacterGun_Mesh->bOwnerNoSee = true;

	FPS_Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("FPSCamera"));
	FPS_Camera->SetupAttachment(Character_Mesh);
	FPS_Camera->FieldOfView = 100;
	FPS_Camera->bUsePawnControlRotation = true;

	FPS_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FPS_Mesh"));
	FPS_Mesh->SetupAttachment(FPS_Camera);
	FPS_Mesh->bOnlyOwnerSee = true;
	FPS_Mesh->bCastDynamicShadow = false;
	FPS_Mesh->CastShadow = false;

	Gun_Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Gun"));
	Gun_Mesh->SetupAttachment(FPS_Mesh);
	Gun_Mesh->bOnlyOwnerSee = true;
	Gun_Mesh->bCastDynamicShadow = false;
	Gun_Mesh->CastShadow = false;

}

// Called when the game starts or when spawned
void AFPS_Character::BeginPlay()
{
	Super::BeginPlay();
	check(GEngine);	
	PC = Cast<AFPS_PlayerController>(this->GetController());
	UWorld* World = GetWorld();
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	if (FPS_Scope)
	{	
		Scope=World->SpawnActor<AScope>(FPS_Scope,SpawnParams);
		Scope->AttachToComponent(Gun_Mesh,FAttachmentTransformRules::KeepRelativeTransform, TEXT("Scope"));
	}
	FPS_Mesh->HideBoneByName(TEXT("head"), EPhysBodyOp::PBO_MAX);
	PC->GameStart();
}

// Called every frame
void AFPS_Character::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!this->GetVelocity().IsZero() && GetCharacterMovement()->MaxWalkSpeed == 600)
	{
		PC->ClientStartCameraShake(MoveCameraShake);
	}
}

// Called to bind functionality to input
void AFPS_Character::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("Move_Forward", this, &AFPS_Character::Move_Forward);
	PlayerInputComponent->BindAxis("Move_Right", this, &AFPS_Character::Move_Right);
	PlayerInputComponent->BindAxis("Turn", this, &AFPS_Character::AddControllerYawInput);
	PlayerInputComponent->BindAxis("LookUp", this, &AFPS_Character::AddControllerPitchInput);
	PlayerInputComponent->BindAction("Jump",IE_Pressed,this, &AFPS_Character::Start_Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &AFPS_Character::Stop_Jump);
	PlayerInputComponent->BindAction("Fire", IE_Pressed,this, &AFPS_Character::Fire);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &AFPS_Character::Stop_Fire);
	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &AFPS_Character::StartReload);
	PlayerInputComponent->BindAction("Grenade", IE_Pressed, this, &AFPS_Character::Grenade_Shoot);
	PlayerInputComponent->BindAction("TiltLeft", IE_Pressed, this, &AFPS_Character::TiltLeft);
	PlayerInputComponent->BindAction("TiltRight", IE_Pressed, this, &AFPS_Character::TiltRight);
	PlayerInputComponent->BindAction("Aim", IE_Pressed, this, &AFPS_Character::AimorHeavyAttack);
	PlayerInputComponent->BindAction("Aim", IE_Released, this, &AFPS_Character::Stop_Aim);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AFPS_Character::Run);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &AFPS_Character::Stop_Run);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &AFPS_Character::Interact);
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &AFPS_Character::PauseGame);
	PlayerInputComponent->BindAction("ChangeWeapon1", IE_Pressed, this, &AFPS_Character::ChangeWeapon1);
	PlayerInputComponent->BindAction("ChangeWeapon2", IE_Pressed, this, &AFPS_Character::ChangeWeapon2);
	PlayerInputComponent->BindAction("ChangeWeapon3", IE_Pressed, this, &AFPS_Character::ChangeWeapon3);
}
void AFPS_Character::Move_Forward(float value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, value);
	if(value<0) GetCharacterMovement()->MaxWalkSpeed = 600;
}

void AFPS_Character::Move_Right(float value)
{
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, value);
}
void AFPS_Character::AddControllerYawInput(float Val)
{
	if (Val != 0.f && Controller && Controller->IsLocalPlayerController())
	{
		PC = Cast<AFPS_PlayerController>(this->GetController());
		PC->AddYawInput(Val);
	}
}
void AFPS_Character::Start_Jump()
{
	bPressedJump = true;
}
void AFPS_Character::Stop_Jump()
{
	bPressedJump = false;
}
void AFPS_Character::TiltLeft()
{
	FPS_Camera->SetRelativeLocation(FVector{0.0f,0.0f,20.0f + BaseEyeHeight });
}
void AFPS_Character::TiltRight()
{
	FPS_Camera->SetRelativeLocation(FVector{ 0.0f,0.0f,60.0f + BaseEyeHeight });
}
void AFPS_Character::AimorHeavyAttack()
{
	UAnimInstance* WeaponAnimInstance = Cast<UAnimInstance>(Gun_Mesh->GetAnimInstance());
	if (WeaponNow->WeaponType == EWeaponType::Knife)
	{
		if (!WeaponAnimInstance->Montage_IsPlaying(WeaponNow->V_FireMontage) && !WeaponAnimInstance->Montage_IsPlaying(WeaponNow->V_KnifeHeavyMontage))
		KnifeAttack(false);
	}
	else
	{
		if (InReload == false && !GetMovementComponent()->IsFalling() && GetCharacterMovement()->MaxWalkSpeed != 1000)
		{
			PC->SetViewTargetWithBlend(Cast<AActor>(Scope),0.2f);
			InAim = true;
		}
	}
}
void AFPS_Character::Stop_Aim()
{
	PC->SetViewTarget(Cast<AActor>(this));
	InAim = false;
}
void AFPS_Character::Run()
{
	GetCharacterMovement()->MaxWalkSpeed = 1000;
}
void AFPS_Character::Stop_Run()
{
	GetCharacterMovement()->MaxWalkSpeed = 600;
}
void AFPS_Character::AddControllerPitchInput(float Val)
{
	if (Val > 0.f)
	{
		if (this->FPS_Camera->GetComponentRotation().Pitch > -70.0)
		{
			if (Val>5)
			{
				PC->AddPitchInput(5);
			}
			else
			{
				PC->AddPitchInput(Val);
			}
		}
	}
	else
	{
		PC = Cast<AFPS_PlayerController>(this->GetController());
		if (Val < -5)
		{
			PC->AddPitchInput(-5);
		}
		else
		{
			PC->AddPitchInput(Val);
		}
	}
}
bool AFPS_Character::CanJumpInternal_Implementation() const
{
	// Ensure the character isn't currently crouched.
	bool bCanJump = !bIsCrouched;
	// Ensure that the CharacterMovement state is valid
	bCanJump &= GetCharacterMovement()->CanAttemptJump();
	if (bCanJump)
	{
		// Ensure JumpHoldTime and JumpCount are valid.
		if (!bWasJumping || GetJumpMaxHoldTime() <= 0.0f)
		{
			if (JumpCurrentCount == 0 && GetCharacterMovement()->IsFalling())
			{
				bCanJump = JumpCurrentCount + 1 < JumpMaxCount;
			}
			else
			{
				bCanJump = JumpCurrentCount < JumpMaxCount;
			}
		}
		else
		{
			// Only consider JumpKeyHoldTime as long as:
			// A) The jump limit hasn't been met OR
			// B) The jump limit has been met AND we were already jumping
			const bool bJumpKeyHeld = (bPressedJump && JumpKeyHoldTime < GetJumpMaxHoldTime());
			bCanJump = bJumpKeyHeld &&
				((JumpCurrentCount < JumpMaxCount) || (bWasJumping && JumpCurrentCount == JumpMaxCount));
		}
	}
	return bCanJump;
}
void AFPS_Character::Shoot()
{
	UAnimInstance* CharacterAnimInstance = Cast<UAnimInstance>(FPS_Mesh->GetAnimInstance());		
	UAnimInstance* WeaponAnimInstance = Cast<UAnimInstance>(Gun_Mesh->GetAnimInstance());
	if (!CharacterAnimInstance->Montage_IsPlaying(WeaponNow->V_DrawMontage) && !CharacterAnimInstance->Montage_IsPlaying(WeaponNow->V_ReloadMontage)  && GetCharacterMovement()->MaxWalkSpeed != 1000)
	{
		if (WeaponNow->Magazine_Bullet_Number > 0)
		{
			//射击坐标

			FVector StartLocation;
			FVector EndLocation;
			FHitResult Hit{ForceInit};
			FCollisionQueryParams Params;
			CameraLocation = PC->PlayerCameraManager->GetCameraLocation();
			CameraRotation = PC->PlayerCameraManager->GetCameraRotation();
			if (!InAim)
			{
				StartLocation = CameraLocation;
				EndLocation = StartLocation + FPS_Camera->GetForwardVector() * WeaponNow->Weapon_Range;
			}
			else
			{
				StartLocation = CameraLocation;
				EndLocation = StartLocation + Scope->GetActorForwardVector()* WeaponNow->Weapon_Range;
			}
			
			//射击时颤动

			if (!InAim)
			{
				PC->ClientStartCameraShake(FireCameraShake);
				AddControllerPitchInput(UKismetMathLibrary::RandomFloatInRange(-0.5,0));
				AddControllerYawInput(UKismetMathLibrary::RandomFloatInRange(-0.25, 0.25));
			}
			else
			{
				PC->ClientStartCameraShake(AimCameraShake);
				AddControllerPitchInput(UKismetMathLibrary::RandomFloatInRange(-0.1, 0));
				AddControllerYawInput(UKismetMathLibrary::RandomFloatInRange(-0.1, 0.1));
			}

			//子弹相关

			
			if (WeaponNow->Shell)
			{
				FActorSpawnParameters SpawnParams;
				SpawnParams.Owner = this;
				SpawnParams.Instigator = GetInstigator();
				AShell* Shell = this->GetWorld()->SpawnActor<AShell>(WeaponNow->Shell, Gun_Mesh->GetSocketLocation("Shell"), Gun_Mesh->GetSocketRotation("Shell"), SpawnParams);
			}
			WeaponNow->Magazine_Bullet_Number--;

			//动画相关

			if (WeaponAnimInstance != nullptr )
			{
				WeaponAnimInstance->Montage_Play(WeaponNow->V_FireMontage, 1.f);
			}
			if (CharacterAnimInstance)
			{
				CharacterAnimInstance->Montage_Play(WeaponNow->V_CharacterFireMontage, 1.f);
			}

			//命中结果

			Params.bTraceComplex = true;
			Params.bReturnPhysicalMaterial = false;
			Params.AddIgnoredActor(this);
			GetWorld()->LineTraceSingleByChannel(Hit,StartLocation,EndLocation, ECC_GameTraceChannel2,Params);
			DrawDebugLine(this->GetWorld(), StartLocation, EndLocation, FColor::Red,true);
			if (Hit.GetActor())	
			{
				PC->ProjectileCount += 1;
				if(HitEmitter)	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEmitter, Hit.Location);
				if(FPS_Hit_Audio)	UGameplayStatics::PlaySoundAtLocation(GetWorld(), FPS_Hit_Audio, Hit.Location);
				if (Hit.GetActor()->GetClass()->IsChildOf(AFloatingActor::StaticClass()))
				{
					Hit.GetActor()->Destroy();
				}
				else
				{
					if (Hit.GetActor()->ActorHasTag(TEXT("Floor")))
					{
						GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, TEXT("Floor"));
						if (Bullet_HoleLight)
						{
							UDecalComponent* Bullet_Decal = UGameplayStatics::SpawnDecalAttached(Bullet_HoleLight, Bullet_Hole_Size, Hit.GetComponent(), NAME_None, Hit.Location, Hit.ImpactNormal.Rotation(), EAttachLocation::KeepWorldPosition, 5.0f);
							Bullet_Decal->SetFadeScreenSize(0.0f);
						}
					}
					else
					{
						if (Bullet_Hole)
						{
							UDecalComponent* Bullet_Decal = UGameplayStatics::SpawnDecalAttached(Bullet_HoleLight, Bullet_Hole_Size, Hit.GetComponent(), NAME_None, Hit.Location, Hit.ImpactNormal.Rotation(), EAttachLocation::KeepWorldPosition, 5.0f);
							Bullet_Decal->SetFadeScreenSize(0.0f);
						}
					}
				}
				UGameplayStatics::ApplyDamage(Hit.GetActor(),WeaponNow->Weapon_Damage,nullptr,this,UDamageType::StaticClass());
			}
		}
	}	
}
void AFPS_Character::KnifeAttack(bool Type)
{
	UAnimInstance* CharacterAnimInstance = Cast<UAnimInstance>(FPS_Mesh->GetAnimInstance());
	UAnimInstance* WeaponAnimInstance = Cast<UAnimInstance>(Gun_Mesh->GetAnimInstance());
	if (!CharacterAnimInstance->Montage_IsPlaying(WeaponNow->V_DrawMontage) && !CharacterAnimInstance->Montage_IsPlaying(WeaponNow->V_ReloadMontage) &&  GetCharacterMovement()->MaxWalkSpeed != 1000)
	{
		FVector StartLocation;
		FVector EndLocation;
		FHitResult Hit{ ForceInit };
		FCollisionQueryParams Params;
		CameraLocation = PC->PlayerCameraManager->GetCameraLocation();
		CameraRotation = PC->PlayerCameraManager->GetCameraRotation();
		StartLocation = CameraLocation;
		EndLocation = StartLocation + FPS_Camera->GetForwardVector() * WeaponNow->Weapon_Range;
		Params.bTraceComplex = true;
		Params.bReturnPhysicalMaterial = false;
		Params.AddIgnoredActor(this);
		GetWorld()->LineTraceSingleByChannel(Hit, StartLocation, EndLocation, ECC_GameTraceChannel2, Params);
		DrawDebugLine(this->GetWorld(), StartLocation, EndLocation, FColor::Red, true);

	
		if (Type)
		{
			if (WeaponAnimInstance)
			{
				WeaponAnimInstance->Montage_Play(WeaponNow->V_FireMontage, 1.f);
			}
			if (CharacterAnimInstance)
			{
				CharacterAnimInstance->Montage_Play(WeaponNow->V_CharacterFireMontage, 1.f);
			}
			UGameplayStatics::ApplyDamage(Hit.GetActor(), WeaponNow->Weapon_Damage, nullptr, this, UDamageType::StaticClass());
			if (Hit.GetActor())
			{
				if (Hit.GetActor()->GetClass()->IsChildOf(AFPS_Enemy::StaticClass()))
				{
					if (FPS_KnifeLight_Audio)	UGameplayStatics::PlaySoundAtLocation(GetWorld(), FPS_KnifeLight_Audio, Hit.Location);
				}
			}
		}	
			
		else
		{
			if (Hit.GetActor())
			{
				if (Hit.GetActor()->GetClass()->IsChildOf(AFPS_Enemy::StaticClass()))
				{
					if (FPS_KnifeHeavy_Audio)	UGameplayStatics::PlaySoundAtLocation(GetWorld(), FPS_KnifeHeavy_Audio, Hit.Location);
				}
			}
			if (WeaponAnimInstance)
			{
				WeaponAnimInstance->Montage_Play(WeaponNow->V_KnifeHeavyMontage, 1.f);
			}
			if (CharacterAnimInstance)
			{
				CharacterAnimInstance->Montage_Play(WeaponNow->V_CharacterKnifeHeavyMontage, 1.f);
			}
			UGameplayStatics::ApplyDamage(Hit.GetActor(), WeaponNow->HeavyAttack_Damage, nullptr, this, UDamageType::StaticClass());
		}
	}
	
}
void AFPS_Character::Fire()
{
	UAnimInstance* WeaponAnimInstance = Cast<UAnimInstance>(Gun_Mesh->GetAnimInstance());
	if (WeaponNow->WeaponType == EWeaponType::Knife)
	{
		if (!WeaponAnimInstance->Montage_IsPlaying(WeaponNow->V_FireMontage) && !WeaponAnimInstance->Montage_IsPlaying(WeaponNow->V_KnifeHeavyMontage))
		KnifeAttack(true);
	}
	else
	{
		if(WeaponNow->IsAuto)
		{
			GetWorldTimerManager().UnPauseTimer(Fire_TimeHandle);
			GetWorldTimerManager().SetTimer(Fire_TimeHandle, this, &AFPS_Character::Shoot, WeaponNow->Weapon_Rate, true,0.0f);
		}
		else
		{
			if(!WeaponAnimInstance->Montage_IsPlaying(WeaponNow->V_FireMontage))
			Shoot();
		}
		if(WeaponNow->Magazine_Bullet_Number<=0)
		{
			if (FPS_CannotShoot_Audio) UGameplayStatics::PlaySoundAtLocation(GetWorld(), FPS_CannotShoot_Audio, GetActorLocation());
		}
	}
}
void AFPS_Character::Stop_Fire()
{
	GetWorldTimerManager().PauseTimer(Fire_TimeHandle);
}
void AFPS_Character::ChangeWeapon1()
{
	ChangeWeapon(0);
}
void AFPS_Character::ChangeWeapon2()
{
	ChangeWeapon(1);
}
void AFPS_Character::ChangeWeapon3()
{
	ChangeWeapon(2);
}
void AFPS_Character::ChangeWeapon(int i)
{
	if (Weapons[i])
	{
		WeaponNow = Weapons[i];
		FPS_Mesh->SetAnimInstanceClass(WeaponNow->V_Character_Anim);
		Gun_Mesh->SetSkeletalMesh(WeaponNow->V_Gun_Mesh);
		Gun_Mesh->SetAnimInstanceClass(WeaponNow->V_Gun_Anim);
		UAnimInstance* CharacterAnimInstance = Cast<UAnimInstance>(FPS_Mesh->GetAnimInstance());
		UAnimInstance* WeaponAnimInstance = Cast<UAnimInstance>(Gun_Mesh->GetAnimInstance());
		if(CharacterAnimInstance && WeaponAnimInstance)
		{
			CharacterAnimInstance->Montage_Play(WeaponNow->V_CharacterDrawMontage, 1.f);
			WeaponAnimInstance->Montage_Play(WeaponNow->V_DrawMontage, 1.f);
		}
		GetWorldTimerManager().ClearTimer(Reload_TimeHandle);
	}
	else
	{

	}
	
}
void AFPS_Character::StartReload()
{
	if (WeaponNow->WeaponType == EWeaponType::Knife)
	{

	}
	else
	{
		GetWorldTimerManager().UnPauseTimer(Reload_TimeHandle);
		UAnimInstance* CharacterAnimInstance = Cast<UAnimInstance>(FPS_Mesh->GetAnimInstance());
		UAnimInstance* RifleAnimInstance = Cast<UAnimInstance>(Gun_Mesh->GetAnimInstance());
		if (RifleAnimInstance != nullptr && CharacterAnimInstance != nullptr && WeaponNow->Max_Magazine!= WeaponNow->Magazine_Bullet_Number && WeaponNow->Spare_Bullet_Number != 0)
		{
			if (!CharacterAnimInstance->Montage_IsPlaying(WeaponNow->V_ReloadMontage) && !CharacterAnimInstance->Montage_IsPlaying(WeaponNow->V_DrawMontage))
			{
				CharacterAnimInstance->Montage_Play(WeaponNow->V_CharacterReloadMontage, 1.f);
				RifleAnimInstance->Montage_Play(WeaponNow->V_ReloadMontage, 1.f);
				InReload = true;
			}
		}
		GetWorldTimerManager().SetTimer(Reload_TimeHandle, this, &AFPS_Character::Reload, 0.1f, false, WeaponNow->Reload_Time);
	}
}

void AFPS_Character::Grenade_Shoot()
{
	if (BulletClass)
	{
		GetActorEyesViewPoint(CameraLocation, CameraRotation);
		Scope->GetActorEyesViewPoint(CameraLocation, CameraRotation);
		MuzzleOffset.Set(100.0f, 27.0f, 16.5f);
		FVector MuzzleLocation = CameraLocation + FTransform(CameraRotation).TransformVector(MuzzleOffset);
		FRotator MuzzleRotation = CameraRotation;
		MuzzleRotation.Pitch += 10.0f;
		UWorld* World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = this;
			SpawnParams.Instigator = GetInstigator();
			AFPS_Bullet* Bullet = World->SpawnActor<AFPS_Bullet>(BulletClass, MuzzleLocation, MuzzleRotation, SpawnParams);
			if (Bullet)
			{
				FVector LunchDirection = MuzzleRotation.Vector();
				Bullet->FireDirection(LunchDirection);
				if (FPS_Grenade_Audio)
				{
					UGameplayStatics::PlaySoundAtLocation(GetWorld(), FPS_Grenade_Audio, GetActorLocation()); 
				}
				PC->ProjectileCount += 1;
			}
		}
	}
}
float AFPS_Character::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Character_Health -= Damage;
	if (Character_Health <= 0)
	{
		IsDead = true;
		FPS_Mesh->SetSimulatePhysics(true);
		this->GetCapsuleComponent()->DestroyComponent();
		PC->PCDead();
		GetWorldTimerManager().UnPauseTimer(Dead_TimeHandle);
		GetWorldTimerManager().SetTimer(Dead_TimeHandle, this, &AFPS_Character::Dead, 3.0f, false, 3.0f);
		PrimaryActorTick.bCanEverTick = false;
	}
	return 0.0f;
}
void AFPS_Character::Dead()
{
	UGameplayStatics::SetGamePaused(this->GetWorld(),true);
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Yellow, FString::Printf(TEXT("Dead")));
}
void AFPS_Character::Reload()
{
	if (WeaponNow->Spare_Bullet_Number >= (WeaponNow->Max_Magazine - WeaponNow->Magazine_Bullet_Number))
	{
		WeaponNow->Spare_Bullet_Number -= (WeaponNow->Max_Magazine- WeaponNow->Magazine_Bullet_Number);
		WeaponNow->Magazine_Bullet_Number = WeaponNow->Max_Magazine;
	}
	else
	{
		WeaponNow->Magazine_Bullet_Number += WeaponNow->Spare_Bullet_Number;
		WeaponNow->Spare_Bullet_Number = 0;
	}
	InReload = false;
	GetWorldTimerManager().PauseTimer(Reload_TimeHandle);
}
void AFPS_Character::Interact()
{
	CameraLocation = PC->PlayerCameraManager->GetCameraLocation();
	CameraRotation = PC->PlayerCameraManager->GetCameraRotation();
	FVector StartLocation = CameraLocation;
	FVector EndLocation = StartLocation + FPS_Camera->GetForwardVector() * 200;
	FCollisionQueryParams Params;
	Params.bTraceComplex = true;
	Params.bReturnPhysicalMaterial = false;
	Params.AddIgnoredActor(this);
	GetWorld()->LineTraceSingleByChannel(Act, StartLocation, EndLocation, ECC_GameTraceChannel3, Params);
	DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, 10.0f, 10, 10.0f);
	if (Act.GetActor())
	{
		if (Act.GetActor()->GetClass()->IsChildOf(AShiftDoor::StaticClass()))
		{
			Cast<AShiftDoor>(Act.GetActor())->Shift();
		}
		if (Act.GetActor()->GetClass()->IsChildOf(AInGameButton::StaticClass()))
		{
			Cast<AInGameButton>(Act.GetActor())->Interact();
		}
	}
}
void AFPS_Character::PauseGame()
{
	UGameplayStatics::SetGamePaused(this->GetWorld(), true);
	PC->PauseGame();
}
