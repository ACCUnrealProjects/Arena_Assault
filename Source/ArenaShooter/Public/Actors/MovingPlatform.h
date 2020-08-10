// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class ARENASHOOTER_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* MyMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveInfo", meta = (AllowPrivateAccess = "true"))
	FVector MovePoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MoveInfo", meta = (AllowPrivateAccess = "true"))
	bool LoopMove = false;

	FVector StartPos;
	bool AmIActive = false;
	bool AmIMovingToPoint = false;

protected:
	virtual void BeginPlay() override;

public:	

	AMovingPlatform();

	virtual void Tick(float DeltaTime) override;

	void MoveToPoint();

	void MoveBack();

	void ActivateMove();

};
