// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponTypeEnum.h"
#include "PickUps/PickUps.h"
#include "WeaponPickUps.generated.h"
/**
 * 
 */
UCLASS()
class ARENASHOOTER_API AWeaponPickUps : public APickUps
{
	GENERATED_BODY()

private:

	virtual bool TriggerPickUp(class AActor* OtherActor) override;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "WeaponPickedUp")
	TSubclassOf<class ABase_Weapon> NewWeapon;

	GunType myWeaponType = GunType::None;

public:
	
	AWeaponPickUps();

};
