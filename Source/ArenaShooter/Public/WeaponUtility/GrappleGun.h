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

private:
	class ACharacter* OwnerCharacter;

	bool ActiveGrapple = false;

	bool ConnectionMade = false;

	bool AttachedActorMoveable = false;

	FVector CableEndPoint = FVector(0);

	void PullOwnerToEnd();

	void GrappleConnect(float DeltaTime);

	FCollisionQueryParams GrappleShotParams;

	UPROPERTY(EditDefaultsOnly, Category = "GrappleProperties", meta = (AllowPrivateAccess = "true"))
	float GrappleRange = 5000.0f;

	UPROPERTY(EditDefaultsOnly, Category = "GrappleProperties", meta = (AllowPrivateAccess = "true"))
	float GrapplePullForce = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GrappleMesh", meta = (AllowPrivateAccess = "true"))
	class USceneComponent* GrappleShooter = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GrappleRope", meta = (AllowPrivateAccess = "true"))
	class UGrabbleCable* GrappleCable = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GrappleSpawnActor", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> GrappleEndActorBP = nullptr;

protected:

	AActor* GrappleEndActor = nullptr;

	AActor* ActorGrappleHit = nullptr;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	AGrappleGun();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void SetMyOwner(AActor* GOwner);

	void GrappleAttempt(FVector GrappleStart, FRotator GrappleDir);

	void DropGrapple();
};
