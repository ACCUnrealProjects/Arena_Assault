// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Public/Controllers/EnemyController.h"
#include "TurretController.generated.h"

/**
 * 
 */
UCLASS()
class ARENASHOOTER_API ATurretController : public AEnemyController
{
	GENERATED_BODY()

private:

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void PawnHasDiedListener();

	virtual void SetPawn(APawn* const InPawn) override;

	virtual void OnPossess(APawn* const InPawn) override;

	UFUNCTION()
	void OnTargetDetected(AActor* actor, FAIStimulus const stimulus);

	virtual void SetupPerceptionSystem() override;

public:

	ATurretController();

	//virtual void Tick(float DeltaTime) override;
	
};
