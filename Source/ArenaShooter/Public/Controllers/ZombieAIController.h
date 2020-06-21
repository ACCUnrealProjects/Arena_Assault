// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ZombieAIController.generated.h"

/**
 * 
 */
UCLASS()
class ARENASHOOTER_API AZombieAIController : public AAIController
{
	GENERATED_BODY()

private:

	APawn* PlayerPawn = nullptr;

	UFUNCTION()
	void PawnHasDiedListener();

	virtual void SetPawn(APawn* InPawn) override;

protected:

public:
	
};
