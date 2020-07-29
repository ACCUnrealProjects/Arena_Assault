// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TurretAimingComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARENASHOOTER_API UTurretAimingComponent : public UActorComponent
{
	GENERATED_BODY()


private:

	class UTurretMesh* ActorTurretMesh = nullptr;
	class UBarrelMesh* ActorBarrelMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "AimingShot", meta = (AllowPrivateAccess = "true"))
	float DegreesCloseToShot = 5.0f;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	

	UTurretAimingComponent();

	void SetUp(class UTurretMesh* MyTurret, class UBarrelMesh* MyBarrel);

	void AimToTarget(FVector TargetPosition);

	bool CloseToHittingTarget(FVector TargetPosition);
};
