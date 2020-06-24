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
	class ACharacter* OwnerCharacter;

	bool ActiveGrapple = false;

	bool ConnectionMade = false;

	FVector CableEndPoint = FVector(0);

	void PullOwnerToEnd();

	void GrappleConnect(float DeltaTime);

	FCollisionQueryParams GrappleShotParams;

protected:

	UPROPERTY(EditDefaultsOnly, Category = "GrappleProperties")
	float GrappleRange = 10000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "GrappleProperties")
	float GrapplePullForce = 50.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GrappleMesh")
	class USceneComponent* GrappleShooter = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GrappleRope")
	class UGrabbleCable* GrappleCable = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GrappleSpawnActor")
	TSubclassOf<AActor> GrappleEndActorBP = nullptr;

	AActor* GrappleEndActor = nullptr;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetMyOwner(AActor* GOwner);

	void GrappleAttempt(FVector GrappleStart, FRotator GrappleDir);

	void DropGrapple();
};
