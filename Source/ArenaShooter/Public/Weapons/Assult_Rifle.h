// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/Base_Weapon.h"
#include "Assult_Rifle.generated.h"

/**
 * 
 */
class UAnimMontage;

UCLASS()
class ARENASHOOTER_API AAssult_Rifle : public ABase_Weapon
{
	GENERATED_BODY()

private:


protected:


public:

	AAssult_Rifle();

	virtual void Fire(FVector FirePoint, FRotator FireDirRotator) override;
	
};
