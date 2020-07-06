// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/AI/GetTargetLocation.h"
#include "../Public/Controllers/ZombieAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "NavigationSystem.h"

UGetTargetLocation::UGetTargetLocation()
{
	NodeName = TEXT("Get Target Location");
}

EBTNodeResult::Type UGetTargetLocation::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	auto const MyZombieAI = Cast<AZombieAIController>(owner_comp.GetAIOwner());
	auto const TargetActor = MyZombieAI->GetBlackboard()->GetValueAsObject(GetSelectedBlackboardKey());
	if (!TargetActor) { return EBTNodeResult::Failed; }
	FVector const TargetPos = Cast<AActor>(TargetActor)->GetActorLocation();



	if (search_random)
	{
		FNavLocation NavLocation;

		UNavigationSystemV1* const Navsystem = UNavigationSystemV1::GetCurrent(GetWorld());
		if (!Navsystem) { return EBTNodeResult::Failed; }
		if (Navsystem->GetRandomPointInNavigableRadius(TargetPos, search_range, NavLocation, nullptr))
		{
			MyZombieAI->GetBlackboard()->SetValueAsVector(TargetLocationKey.SelectedKeyName, NavLocation.Location);
		}
	}
	else
	{
		MyZombieAI->GetBlackboard()->SetValueAsVector(TargetLocationKey.SelectedKeyName, TargetPos);
	}

	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}