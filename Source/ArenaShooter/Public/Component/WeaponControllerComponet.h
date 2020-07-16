// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponTypeEnum.h"
#include "WeaponControllerComponet.generated.h"

class ABase_Weapon;
class USkeletalMeshComponent;
class UAnimMontage;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARENASHOOTER_API UWeaponControllerComponet : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponControllerComponet();

private:
	bool IsFiring = false;

	// Info for where to attach new guns to
	USkeletalMeshComponent* WeaponAttachSkel = nullptr;
	FString PointInSkel;

	FActorSpawnParameters SpawnParams;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	TArray<ABase_Weapon*> MyGuns;

	TArray<GunType> GunSlots;

	UPROPERTY(BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	ABase_Weapon* CurrentWeapon = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	TMap<GunType, UAnimMontage*> FireAnimations;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Animations", meta = (AllowPrivateAccess = "true"))
	TMap<GunType, UAnimMontage*> ReloadAnimations;

protected:
	virtual void BeginPlay() override;

public:	
	//Adding New Gun
	void AddGun(TSubclassOf<ABase_Weapon> NewWeapon, GunType myWeaponType);
	void SetAttachSkel(USkeletalMeshComponent* AttachWeaponTo, FString PointToAttachTo);
	bool DoIAlreadyHaveGun(GunType NewGunType);

	//Get current gun
	ABase_Weapon* GetCurrentGun();

	//Weapon Controls
	void FireCurrentWeapon(FVector FirePoint, FRotator FireDirRotator);
	void Reload();
	void StopFire();
	void ChangeGun(GunType SwitchGunType);
};
