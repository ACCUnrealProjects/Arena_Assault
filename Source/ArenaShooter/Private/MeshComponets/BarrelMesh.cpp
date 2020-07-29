// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/MeshComponets/BarrelMesh.h"

void UBarrelMesh::RotateBarrel(float ElevateSpeed)
{
	UE_LOG(LogTemp, Warning, TEXT("Barrel elevate speed is %f"), ElevateSpeed);
	float PitchChange = (FMath::Clamp<float>(ElevateSpeed, -1, +1)) * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	float PitchTurn = FMath::Clamp<float>(GetRelativeRotation().Pitch + PitchChange, MinTurn, MaxTurn);
	SetRelativeRotation(FRotator(PitchTurn, 0, 0));
}
