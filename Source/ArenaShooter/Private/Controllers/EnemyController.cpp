// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Controllers/EnemyController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"


AEnemyController::AEnemyController()
{
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
	BlackBoardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
}


void AEnemyController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTree);
	BehaviorTreeComp->StartTree(*BehaviorTree);
}


void AEnemyController::SetupPerceptionSystem()
{
	AISightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AI Sight"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception Comp")));
}

void AEnemyController::SetPawn(APawn* const InPawn)
{
	Super::SetPawn(InPawn);

}

void AEnemyController::OnPossess(APawn* const InPawn)
{
	Super::OnPossess(InPawn);
	if (BlackBoardComp)
	{
		BlackBoardComp->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	}
}


UBlackboardComponent* AEnemyController::GetBlackboard() const
{
	return BlackBoardComp;
}
