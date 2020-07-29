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
	//AActor* const TargetActor = Cast<AActor>(MyZombieAI->GetBlackboard()->GetValueAsObject(GetSelectedBlackboardKey()));

	UAIBlueprintHelperLibrary::SimpleMoveToLocation(MyZombieAI, MyZombieAI->GetBlackboard()->GetValueAsVector(GetSelectedBlackboardKey()));
	//UAIBlueprintHelperLibrary::SimpleMoveToActor(MyZombieAI, TargetActor);

	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}