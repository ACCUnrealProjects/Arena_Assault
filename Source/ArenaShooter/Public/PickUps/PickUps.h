// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickUps.generated.h"

UCLASS()
class ARENASHOOTER_API APickUps : public AActor
{
	GENERATED_BODY()
	
private:

	virtual void TriggerPickUp(class AActor* OtherActor) PURE_VIRTUAL(APickUps::TriggerPickUp, return; );

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	class UStaticMeshComponent* PickUpMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	class UCapsuleComponent* PickUpCollider = nullptr;

public:	
	APickUps();

	UFUNCTION()
	void BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
