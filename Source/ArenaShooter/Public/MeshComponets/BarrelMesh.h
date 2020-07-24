// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "BarrelMesh.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class ARENASHOOTER_API UBarrelMesh : public UStaticMeshComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly, Category = "BarrelMovement", meta = (AllowPrivateAccess = "true"))
	float MaxDegreesPerSecond = 25;

	UPROPERTY(EditDefaultsOnly, Category = "BarrelMovement", meta = (AllowPrivateAccess = "true"))
	float MinTurn = 0.0f;

	UPROPERTY(EditDefaultsOnly, Category = "BarrelMovement", meta = (AllowPrivateAccess = "true"))
	float MaxTurn = 40.0f;


public:
	void RotateBarrel(float ElevateSpeed);

};
