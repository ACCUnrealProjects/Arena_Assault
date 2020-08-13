// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Controllers/MainPlayerController.h"
#include "../Public/Component/HealthComponent.h"
#include "Kismet/GameplayStatics.h"

AMainPlayerController::AMainPlayerController()
{

}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AMainPlayerController::MyPawnHasDied()
{
	StartSpectatingOnly();
	UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), true);

}

void AMainPlayerController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		UHealthComponent* PawnsHealthCon = InPawn->FindComponentByClass<UHealthComponent>();
		if (!ensure(PawnsHealthCon)) { return; }
		PawnsHealthCon->IHaveDied.AddUniqueDynamic(this, &AMainPlayerController::MyPawnHasDied);
	}
}