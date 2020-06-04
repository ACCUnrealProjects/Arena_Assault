// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Base_Weapon.h"
#include "Pistol.generated.h"

/**
 * 
 */
UCLASS()
class ARENASHOOTER_API APistol : public ABase_Weapon
{
	GENERATED_BODY()

private:


protected:

	float Range = 10000.0f;

public:

	APistol();

	virtual void Fire(FVector FirePoint, FRotator FireDirRotator) override;
	
};
