// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ARENASHOOTER_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()
	
private:

	uint32 Score = 0;

	UFUNCTION()
	void MyPawnHasDied();

	virtual void SetPawn(APawn* InPawn) override;

protected:

	virtual void BeginPlay() override;

public:

	AMainPlayerController();

};
