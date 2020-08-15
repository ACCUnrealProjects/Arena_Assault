// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class ARENASHOOTER_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

private:

	//DamageEffectFunctions
	UFUNCTION()
	void TakenDamage();
	void DamageEffectTimeDecrease();

	//Grapple Controls
	void FireGrapple();
	void GrappleRelease();

	//Wall Run Functions
	void WallRunning(float DeltaSeconds);
	void EndWallRun();

	//Death
	virtual void Destroyed() override;

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StartingWeapon", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ABase_Weapon> StartWeapon = nullptr;

	class UMaterialParameterCollectionInstance* HitMaterialParameterinst = nullptr;
	class UCharacterMovementComponent* MyMoveComp = nullptr;
	class USkeletalMeshComponent* SM_Arms;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "HitPostProcessing", meta = (AllowPrivateAccess = "true"))
	class UMaterialParameterCollection* HitMaterialParameter = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "HealthComponent", meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* MyHealthComp = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WallRunCollision", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* WallRunCap = nullptr;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"), meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* MyCamera = nullptr;

	// Custom comps
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "GrappleController", meta = (AllowPrivateAccess = "true"))
	class UGrappleControlComponent* MyGrappleController;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "WeaponController", meta = (AllowPrivateAccess = "true"))
	class UWeaponControllerComponet* MyWeaponController = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "DashComponent", meta = (AllowPrivateAccess = "true"))
	class UCharacterDashComponent* MyDashComp = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Movement", meta = (AllowPrivateAccess = "true"))
	FVector JumpVel = FVector(0, 0, 450);

	// WallRunInfo
	FVector WallRunDir;
	bool bAmIWallRunning = false;
	FHitResult WallRayCast;
	AActor* CurrentWall = nullptr;
	float StartRoll = 0.0f;
	float TargetRoll = 0.0f;

	// Condition Values
	bool bTakenDamageEffectOn = false;
	bool bWeWantToFire = false;
	bool bJumpBeingHeld = false;

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
	void JumpReleased();
	void Dash();

	//Weapon Controls
	void SetFire();
	void StopFire();
	void Reload();

	//Change Gun
	void ChangeGunOne();
	void ChangeGunTwo();
	void ChangeGunThree();

	//Jump Values
	float JumpsUsed = 0;

public:
	// Sets default values for this character's properties
	APlayerCharacter();
};
