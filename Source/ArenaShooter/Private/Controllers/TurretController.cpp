// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Controllers/TurretController.h"
#include "../Public/Component/HealthComponent.h"
#include "../Public/Enemy/Turret.h"
#include "GameFramework/Character.h"
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
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
	BlackBoardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
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
	AISightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AI Sight"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception Comp")));
	AISightConfig->SightRadius = 1000.0f;
	AISightConfig->LoseSightRadius = AISightConfig->SightRadius * 1.1f;
	AISightConfig->PeripheralVisionAngleDegrees = 360.0f;
	AISightConfig->SetMaxAge(2.0f);
	AISightConfig->AutoSuccessRangeFromLastSeenLocation = 900.0f;
	AISightConfig->DetectionByAffiliation.bDetectEnemies = true;
	AISightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	AISightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*AISightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &ATurretController::OnTargetDetected);
	GetPerceptionComponent()->ConfigureSense(*AISightConfig);
}

void ATurretController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTree);
	BehaviorTreeComp->StartTree(*BehaviorTree);
}

void ATurretController::OnPossess(APawn* const InPawn)
{
	Super::OnPossess(InPawn);
	if (BlackBoardComp)
	{
		BlackBoardComp->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	}
}

void ATurretController::SetPawn(APawn* const InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		UHealthComponent* PawnsHealthCon = InPawn->FindComponentByClass<UHealthComponent>();
		if (!ensure(PawnsHealthCon)) { return; }
		PawnsHealthCon->IHaveDied.AddUniqueDynamic(this, &ATurretController::PawnHasDiedListener);
	}
}


void ATurretController::PawnHasDiedListener()
{
	if (!GetPawn()) { return; }
	GetWorld()->DestroyActor(GetPawn());
}

UBlackboardComponent* ATurretController::GetBlackboard() const
{
	return BlackBoardComp;
}

