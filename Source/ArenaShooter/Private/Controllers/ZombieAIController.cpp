// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Controllers/ZombieAIController.h"
#include "../Public/Component/HealthComponent.h"

void AZombieAIController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		UHealthComponent* PawnsHealthCon = InPawn->FindComponentByClass<UHealthComponent>();
		if (!ensure(PawnsHealthCon)) { return; }
		PawnsHealthCon->IHaveDied.AddUniqueDynamic(this, &AZombieAIController::PawnHasDiedListener);
	}
}

void AZombieAIController::PawnHasDiedListener()
{
	if (!GetPawn())
	{
		return;
	}
	GetPawn()->DetachFromControllerPendingDestroy();
}
