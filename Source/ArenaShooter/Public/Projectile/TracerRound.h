// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TracerRound.generated.h"

UCLASS()
class ARENASHOOTER_API ATracerRound : public AActor
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	class UShapeComponent* SphereCollider = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* TraceMesh = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement = nullptr;

protected:

	virtual void BeginPlay() override;

public:	

	ATracerRound();

	//virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void TracerHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
