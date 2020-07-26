// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Controllers/ZombieAIController.h"
#include "../Public/Component/HealthComponent.h"
#include "../Public/Enemy/Zombie.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"

AZombieAIController::AZombieAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("BehaviorTree'/Game/MyStuff/AI/Zombie_AI_BT.Zombie_AI_BT'"));
	if (obj.Succeeded())
	{
		BehaviorTree = obj.Object;
	}
	SetupPerceptionSystem();

}

void AZombieAIController::OnTargetDetected(AActor* actor, FAIStimulus const stimulus)
{
	if (actor && actor == Cast<AActor>(GetWorld()->GetFirstPlayerController()->GetPawn()))
	{
		GetBlackboard()->SetValueAsBool(TEXT("CanSeePlayer"), stimulus.WasSuccessfullySensed());
	}
}

void AZombieAIController::SetupPerceptionSystem()
{
	AEnemyController::SetupPerceptionSystem();

	AISightConfig->SightRadius = 2000.0f;
	AISightConfig->LoseSightRadius = AISightConfig->SightRadius * 1.1f;
	AISightConfig->PeripheralVisionAngleDegrees = 360.0f;
	AISightConfig->SetMaxAge(5.0f);
	AISightConfig->AutoSuccessRangeFromLastSeenLocation = 2500.0f;
	AISightConfig->DetectionByAffiliation.bDetectEnemies = true;
	AISightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	AISightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*AISightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AZombieAIController::OnTargetDetected);
	GetPerceptionComponent()->ConfigureSense(*AISightConfig);
}

void AZombieAIController::BeginPlay()
{
	AEnemyController::BeginPlay();
}

void AZombieAIController::OnPossess(APawn* const InPawn)
{
	AEnemyController::OnPossess(InPawn);
}

void AZombieAIController::SetPawn(APawn* const InPawn)
{
	AEnemyController::SetPawn(InPawn);

	if (InPawn)
	{
		UHealthComponent* PawnsHealthCon = InPawn->FindComponentByClass<UHealthComponent>();
		if (!ensure(PawnsHealthCon)) { return; }
		PawnsHealthCon->IHaveDied.AddUniqueDynamic(this, &AZombieAIController::PawnHasDiedListener);
	}
}

void AZombieAIController::PawnHasDiedListener()
{
	if (!GetPawn()) { return; }
	GetWorld()->DestroyActor(GetPawn());
}

