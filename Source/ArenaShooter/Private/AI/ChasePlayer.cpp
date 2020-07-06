// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/AI/ChasePlayer.h"
#include "../Public/Controllers/ZombieAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"


UChasePlayer::UChasePlayer()
{
	NodeName = TEXT("Chase Player");
}

EBTNodeResult::Type UChasePlayer::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	AZombieAIController* const MyZombieAI = Cast<AZombieAIController>(owner_comp.GetAIOwner());
	FVector const TargetLocation = MyZombieAI->GetBlackboard()->GetValueAsVector(GetSelectedBlackboardKey());

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(MyZombieAI, TargetLocation);

	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}