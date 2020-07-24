// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/MeshComponets/TurretMesh.h"

void UTurretMesh::RotateTurret(float TurnSpeed)
{
	float YawChange = (FMath::Clamp<float>(TurnSpeed, -1, +1)) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float YawTurn = FMath::Clamp<float>(GetRelativeRotation().Yaw + YawChange, MinTurn, MaxTurn);
	SetRelativeRotation(FRotator(0, YawTurn, 0));
}
