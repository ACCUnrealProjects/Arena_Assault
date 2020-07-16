// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Base_Weapon.h"
#include "Single_Bullet_Fire.generated.h"

/**
 * 
 */
UCLASS()
class ARENASHOOTER_API ASingle_Bullet_Fire : public ABase_Weapon
{
	GENERATED_BODY()

private:

protected:

	float RecoilCounter;

	float MaxRecoilCounter;

	float RecoilIncrease;

	void Fire(FVector FirePoint, FRotator FireDirRotator) override;

public:

	ASingle_Bullet_Fire();
	
	virtual bool Reload() override;

	virtual void StopFire() override;

};
