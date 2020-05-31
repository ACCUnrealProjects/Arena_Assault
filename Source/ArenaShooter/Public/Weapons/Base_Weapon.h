// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WeaponTypeEnum.h"
#include "Base_Weapon.generated.h"

UENUM(BlueprintType)
enum class WeaponState : uint8
{
	Idle,
	Fireing,
	Reloading,
};

class USceneComponent;
class USkeletalMeshComponent;
class USoundBase;

UCLASS()
class ARENASHOOTER_API ABase_Weapon : public AActor
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ABase_Weapon();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
	int32 MaxAmmo;

	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
	int32 ClipSize;

	UPROPERTY(BlueprintReadOnly, Category = "Ammo")
	int32 CurrentTotalAmmo;

	UPROPERTY(BlueprintReadOnly, Category = "Ammo")
	int32 CurrentClipAmmo;

	UPROPERTY(BlueprintReadOnly, Category = "FireState")
	WeaponState myWeaponState = WeaponState::Idle;

	UPROPERTY(BlueprintReadOnly, Category = "WeaponType")
	GunType myWeaponType = GunType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	USkeletalMeshComponent* GunMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	USceneComponent* Muzzle;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float FireRate;

	float RecoilCounter;

	float MaxRecoilCounter;

	UPROPERTY(EditDefaultsOnly, Category = "Reloading")
	float TotalReloadTime;

	float LastFire = -10.0f;

	float ReloadStartTime = -10.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound")
	USoundBase* FireSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimSequence* FireAnimation = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation")
	UAnimSequence* ReloadAnimation = nullptr;

	AActor* GunOwner = nullptr;

	virtual void Tick(float DeltaTime) override;

	virtual void Fire(FVector FirePoint, FRotator FireDirRotator);

private:

public:

	virtual bool Reload();

	bool DidIFire(FVector FirePoint, FRotator FireDirRotator);

	void StopFire();

	virtual void OnAttach(AActor* MyOwner);

	void ChangeActiveState(bool state);

	bool OutOfAmmo();

	GunType GetGunType();

};
