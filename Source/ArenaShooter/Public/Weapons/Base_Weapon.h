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
	
private:

	UPROPERTY(BlueprintReadOnly, Category = "FireState", meta = (AllowPrivateAccess = "true"))
	WeaponState myWeaponState = WeaponState::Idle;

	UPROPERTY(BlueprintReadOnly, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* FireEffect = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	USoundBase* FireSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	USoundBase* DryClipSound = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	UAnimSequence* FireAnimation = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animation", meta = (AllowPrivateAccess = "true"))
	UAnimSequence* ReloadAnimation = nullptr;

protected:

	UPROPERTY(BlueprintReadOnly, Category = "WeaponType")
	GunType myWeaponType = GunType::None;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	USceneComponent* Muzzle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	USkeletalMeshComponent* GunMesh = nullptr;

	UPROPERTY(BlueprintReadOnly, Category = "Ammo")
	int32 CurrentTotalAmmo;

	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
	int32 MaxAmmo;

	UPROPERTY(EditDefaultsOnly, Category = "Ammo")
	int32 ClipSize;

	UPROPERTY(BlueprintReadOnly, Category = "Ammo")
	int32 CurrentClipAmmo;

	UPROPERTY(BlueprintReadOnly, Category = "Damage")
	int32 DamagePerShot;

	UPROPERTY(BlueprintReadOnly, Category = "Range")
	float Range;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float FireRate;

	UPROPERTY(EditDefaultsOnly, Category = "Reloading")
	float TotalReloadTime;

	float RecoilCounter;

	float MaxRecoilCounter;

	FTimerHandle ReloadTimer;

	float LastFire = -10.0f;

	AActor* GunOwner = nullptr;

	virtual void BeginPlay() override;

	virtual void Fire(FVector FirePoint, FRotator FireDirRotator);

private:

	void ReloadComplete();

	void DeSpawnFireEffect();

public:

	// Sets default values for this actor's properties
	ABase_Weapon();

	virtual bool Reload();

	bool DidIFire(FVector FirePoint, FRotator FireDirRotator);

	void StopFire();

	virtual void OnAttach(AActor* MyOwner);

	void ChangeActiveState(const bool AmIActive);

	bool OutOfAmmo() const;

	void AddAmmo(const int32 Ammo);

	GunType GetGunType() const;

};
