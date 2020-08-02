// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WeaponTypeEnum.h"
#include "PickUps/PickUps.h"
#include "AmmoPickUps.generated.h"

/**
 * 
 */
UCLASS()
class ARENASHOOTER_API AAmmoPickUps : public APickUps
{
	GENERATED_BODY()

private:

	virtual bool TriggerPickUp(class AActor* OtherActor) override;

protected:

	int32 AmmoAmmount;

	GunType myWeaponType = GunType::None;

public:

	AAmmoPickUps();
	
};
