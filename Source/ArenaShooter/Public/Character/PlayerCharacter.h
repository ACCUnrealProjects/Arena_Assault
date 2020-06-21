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
	void JumpReleased();
	void Dash();

	//Weapon Controls
	void SetFire();
	void Reload();

	//Change Gun
	void ChangeGunOne();
	void ChangeGunTwo();
	void ChangeGunThree();

	//Jump Values
	float JumpsUsed = 0;
	UPROPERTY(EditDefaultsOnly, Category = "Movement")
	FVector JumpVel = FVector(0, 0, 450);

	//Jump Dashes
	UPROPERTY(EditDefaultsOnly, Category = "Dashing")
	float DashResetTime = 2.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Dashing")
	float DashDuration = 0.1f;
	UPROPERTY(EditDefaultsOnly, Category = "Dashing")
	float DashingSpeed = 3000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "StartingWeapon")
	TSubclassOf<class ABase_Weapon> StartWeapon = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "HitPostProcessing")
	class UMaterialParameterCollection* HitMaterialParameter = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WeaponController")
	class UWeaponControllerComponet* MyWeaponController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HealthComponent")
	class UHealthComponent* MyHealthComp = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "WallRunCollision")
	class UCapsuleComponent* WallRunCap = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* MyCamera = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "GrappleController")
	class UGrappleControlComponent* MyGrappleController;

public:

private:

	class UCharacterMovementComponent* MyMoveComp = nullptr;

	UPROPERTY(VisibleDefaultsOnly, Category = "Setup")
	class USkeletalMeshComponent* SM_Arms;

	class UMaterialParameterCollectionInstance* HitMaterialParameterinst = nullptr;

	//DamageEffectFunctions
	UFUNCTION()
	void TakenDamage();
	void DamageEffectTimeDecrease();

	//Dash Functions
	void DashEnd();
	void ResetDash();

	//Grapple Controls
	void FireGrapple();
	void GrappleRelease();

	//Wall Run Functions
	void WallRunning(float DeltaSeconds);
	void EndWallRun();

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	// WallRunInfo
	FVector WallRunDir;
	bool bAmIWallRunning = false;
	FHitResult WallRayCast;
	AActor *CurrentWall = nullptr;
	float StartRoll = 0.0f;
	float TargetRoll = 0.0f;

	// Condition Values
	bool bCanDash = true;
	bool bTakenDamageEffectOn = false;
	bool bWeWantToFire = false;
	bool bJumpBeingHeld = false;
};
