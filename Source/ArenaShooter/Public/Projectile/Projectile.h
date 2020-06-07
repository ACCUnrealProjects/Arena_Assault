// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class ARENASHOOTER_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

private:

protected:
	void BeginPlay();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	class UStaticMeshComponent* ProjectileMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	class USphereComponent* MySphereCollider;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	class UProjectileMovementComponent* ProjectileMoveComp;

public:	

};
