// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PickUps/PickUps.h"
#include "HealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class ARENASHOOTER_API AHealthPickup : public APickUps
{
	GENERATED_BODY()

private:

protected:
	int32 HealthAmmount = 25;

	virtual bool TriggerPickUp(class AActor* OtherActor) override;

public:

};
