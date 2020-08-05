// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Controllers/TurretController.h"
#include "../Public/Component/HealthComponent.h"
#include "../Public/Enemy/Turret.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"

ATurretController::ATurretController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("BehaviorTree'/Game/MyStuff/AI/Turret_AI_BT.Turret_AI_BT'"));
	if (obj.Succeeded())
	{
		BehaviorTree = obj.Object;
	}
	SetupPerceptionSystem();
}

void ATurretController::OnTargetDetected(AActor* actor, FAIStimulus const stimulus)
{
	if (actor && actor == Cast<AActor>(GetWorld()->GetFirstPlayerController()->GetPawn()))
	{
		GetBlackboard()->SetValueAsBool(TEXT("CanSeePlayer"), stimulus.WasSuccessfullySensed());
	}
}

void ATurretController::SetupPerceptionSystem()
{
	AEnemyController::SetupPerceptionSystem();

	AISightConfig->SightRadius = 2000.0f;
	AISightConfig->LoseSightRadius = AISightConfig->SightRadius * 1.1f;
	AISightConfig->PeripheralVisionAngleDegrees = 360.0f;
	AISightConfig->SetMaxAge(0.1f);
	AISightConfig->AutoSuccessRangeFromLastSeenLocation = 100.0f;
	AISightConfig->DetectionByAffiliation.bDetectEnemies = true;
	AISightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	AISightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*AISightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ATurretController::OnTargetDetected);
	GetPerceptionComponent()->ConfigureSense(*AISightConfig);
}

void ATurretController::BeginPlay()
{
	AEnemyController::BeginPlay();
}

void ATurretController::OnPossess(APawn* const InPawn)
{
	AEnemyController::OnPossess(InPawn);
}

void ATurretController::SetPawn(APawn* const InPawn)
{
	AEnemyController::SetPawn(InPawn);

	/*if (InPawn)
	{
		UHealthComponent* PawnsHealthCon = InPawn->FindComponentByClass<UHealthComponent>();
		if (!ensure(PawnsHealthCon)) { return; }
		PawnsHealthCon->IHaveDied.AddUniqueDynamic(this, &ATurretController::PawnHasDiedListener);
	}*/
}


void ATurretController::PawnHasDiedListener()
{
	if (!GetPawn()) { return; }
	GetWorld()->DestroyActor(GetPawn());
}


