// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Component/TurretAimingComponent.h"
#include "../Public/MeshComponets/BarrelMesh.h"
#include "../Public/MeshComponets/TurretMesh.h"

// Sets default values for this component's properties
UTurretAimingComponent::UTurretAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UTurretAimingComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTurretAimingComponent::SetUp(UTurretMesh* MyTurret, UBarrelMesh* MyBarrel)
{
	ActorTurretMesh = MyTurret;
	ActorBarrelMesh = MyBarrel;
}

void UTurretAimingComponent::AimToTarget(FVector TargetPosition)
{
	if (!ActorTurretMesh || !ActorBarrelMesh) { return; }

	FVector ToTarget = TargetPosition - ActorBarrelMesh->GetComponentLocation();
	ToTarget = ToTarget.GetSafeNormal();
	FRotator DirectionRotation = ToTarget.Rotation();
	FRotator DesiredChange = DirectionRotation - ActorBarrelMesh->GetForwardVector().Rotation();
	ActorBarrelMesh->RotateBarrel(DesiredChange.Pitch);
	if (DesiredChange.Yaw > 180)
	{
		DesiredChange.Yaw = DesiredChange.Yaw - 360;
	}
	else if (DesiredChange.Yaw < -180)
	{
		DesiredChange.Yaw = DesiredChange.Yaw + 360;
	}
	ActorTurretMesh->RotateTurret(DesiredChange.Yaw);
}

bool UTurretAimingComponent::CloseToHittingTarget(FVector TargetPosition)
{
	if (!ActorTurretMesh || !ActorBarrelMesh) { return false; }

	FVector ToTarget = TargetPosition - ActorTurretMesh->GetComponentLocation();
	ToTarget = ToTarget.GetSafeNormal();

	if (ToTarget.Equals(ActorBarrelMesh->GetForwardVector(), 0.2f))
	{
		return true;
	}

	return false;
}
