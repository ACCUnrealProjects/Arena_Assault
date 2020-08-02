// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Base_Weapon.h"
#include "Shotgun.generated.h"

/**
 * 
 */
UCLASS()
class ARENASHOOTER_API AShotgun : public ABase_Weapon
{
	GENERATED_BODY()

private:

	int32 PelletsPerShot = 6;

protected:


public:

	AShotgun();

	virtual void Fire(FVector FirePoint, FRotator FireDirRotator) override;
	
};
