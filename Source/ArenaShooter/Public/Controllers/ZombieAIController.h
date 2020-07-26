// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "../Public/Controllers/EnemyController.h"
#include "ZombieAIController.generated.h"

/**
 * 
 */
UCLASS()
class ARENASHOOTER_API AZombieAIController : public AEnemyController
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

	AZombieAIController();

	//virtual void Tick(float DeltaTime) override;
	
};
