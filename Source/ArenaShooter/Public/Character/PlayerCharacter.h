// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class ARENASHOOTER_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Landed(const FHitResult& Hit) override;

	// Movement Controls
	void MoveFoward(float Amount);
	void MoveRight(float Amount);
	void Jump();

	//Weapon Controls
	void SetFire();
	void Reload();

	void ChangeGunOne();
	void ChangeGunTwo();
	void ChangeGunThree();

	float JumpsUsed = 0;
	FVector JumpVel = FVector(0, 0, 450);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StartingWeapon")
	TSubclassOf<class ABase_Weapon> StartWeapon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HitPostProcessing")
	class UMaterialParameterCollection* HitMaterialParameter = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponController")
	class UWeaponControllerComponet* MyWeaponController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HealthComponent")
	class UHealthComponent* MyHealthComp = nullptr;

public:

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* MyCamera = nullptr;

	class UCharacterMovementComponent* MyMoveComp = nullptr;

	UPROPERTY(VisibleDefaultsOnly, Category = "Setup")
	class USkeletalMeshComponent* SM_Arms;

	class UMaterialParameterCollectionInstance* HitMaterialParameterinst = nullptr;

	UFUNCTION()
	void TakenDamage();
	void DamageEffectTimeDecrease();
	bool TakenDamageEffect = false;

	bool WeWantToFire = false;
	int8 GunOut = 0;
};
