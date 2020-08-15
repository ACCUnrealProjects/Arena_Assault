// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TurretMesh.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARENASHOOTER_API UTurretMesh : public UStaticMeshComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly, Category = "TurretMovement", meta = (AllowPrivateAccess = "true"))
	float MaxDegreesPerSecond = 270.0f;

	UPROPERTY(EditDefaultsOnly, Category = "TurretMovement", meta = (AllowPrivateAccess = "true"))
	float MinTurn = -360.0f;

	UPROPERTY(EditDefaultsOnly, Category = "TurretMovement", meta = (AllowPrivateAccess = "true"))
	float MaxTurn = 360.0f;

protected:

public:

	void RotateTurret(float TurnSpeed);

};
