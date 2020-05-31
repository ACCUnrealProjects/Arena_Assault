// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
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
	int8 GunOut = 0;

	// Info for where to attach new guns to
	USkeletalMeshComponent* WeaponAttachSkel = nullptr;
	FString PointInSkel;

	FActorSpawnParameters SpawnParams;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons")
	TArray<ABase_Weapon*> MyEquipedGun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UAnimMontage* FireAnimation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Animations")
	UAnimMontage* ReloadAnimation;


public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void AddGun(TSubclassOf<ABase_Weapon> NewWeapon);

	void SetAttachSkel(USkeletalMeshComponent* AttachWeaponTo, FString PointToAttachTo);

	//Weapon Controls
	void FireCurrentWeapon(FVector FirePoint, FRotator FireDirRotator);
	void Reload();
	void StopFire();
	void ChangeGun(int8 WeaponNum);
};
