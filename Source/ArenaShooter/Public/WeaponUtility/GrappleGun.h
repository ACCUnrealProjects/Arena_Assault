// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GrappleGun.generated.h"

UCLASS()
class ARENASHOOTER_API AGrappleGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGrappleGun();

private:

	class AActor* MyOwner;

	bool ActiveGrapple = false;

	bool ConnectionMade = false;

	FVector PullDir = FVector(0);

	FVector CableEndPoint = FVector(0);

	void PullOwnerToEnd();

protected:

	UPROPERTY(EditDefaultsOnly, Category = "GrappleProperties")
	float GrappleRange = 10000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "GrappleProperties")
	float GrapplePullForce = 2000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GrappleMesh")
	class USceneComponent* GrappleShooter = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GrappleRope")
	class UGrabbleCable* GrappleCable = nullptr;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetMyOwner(AActor* GOwner);

	void GrappleAttempt(FRotator Dir);

	void DropGrapple();
};
