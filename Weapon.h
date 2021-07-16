// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Shell.h"
#include "Weapon.generated.h"

UENUM()
enum class EWeaponType
{
	Main,
	Second,
	Knife,
	Granade
};
UCLASS()
class FPS_TEST_API AWeapon : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
		EWeaponType WeaponType;
	UPROPERTY(EditAnywhere)
		USkeletalMesh* V_Gun_Mesh;
	UPROPERTY(EditAnywhere)
		UAnimBlueprintGeneratedClass* V_Gun_Anim;
	UPROPERTY(EditAnywhere)
		UAnimBlueprintGeneratedClass* V_Character_Anim;

	UPROPERTY(EditAnywhere)
		USkeletalMeshComponent*	 W_Gun_Mesh;
	UPROPERTY(EditAnywhere)
		UAnimBlueprintGeneratedClass* W_Gun_Anim;
	UPROPERTY(EditAnywhere)
		UAnimBlueprintGeneratedClass* W_Character_Anim;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<AShell> Shell;
	UPROPERTY(EditAnywhere, Category = Montage)
		class UAnimMontage* V_CharacterReloadMontage;
	UPROPERTY(EditAnywhere, Category = Montage)
		class UAnimMontage* V_ReloadMontage;
	UPROPERTY(EditAnywhere, Category = Montage)
		class UAnimMontage* V_CharacterFireMontage;
	UPROPERTY(EditAnywhere, Category = Montage)
		class UAnimMontage* V_FireMontage;
	UPROPERTY(EditAnywhere, Category = Montage)
		class UAnimMontage* V_CharacterDrawMontage;
	UPROPERTY(EditAnywhere, Category = Montage)
		class UAnimMontage* V_DrawMontage;
	UPROPERTY(EditAnywhere, Category = Montage)
		class UAnimMontage* V_CharacterKnifeHeavyMontage;
	UPROPERTY(EditAnywhere, Category = Montage)
		class UAnimMontage* V_KnifeHeavyMontage;
	UPROPERTY(EditAnywhere)
		int32 Weapon_Range;
	UPROPERTY(EditAnywhere)
		int32 Weapon_Damage;
	UPROPERTY(EditAnywhere)
		int32 HeavyAttack_Damage;
	UPROPERTY(EditAnywhere)
		bool IsAuto;
	UPROPERTY(EditAnywhere)
		float Weapon_Rate;
	UPROPERTY(EditAnywhere)
		int32 Max_Magazine;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Spare_Bullet_Number;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		int32 Magazine_Bullet_Number;
	UPROPERTY(EditAnywhere)
		float Reload_Time;
};
