// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/AI/FindPlayerLocation.h"
#include "../Public/Controllers/EnemyController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "NavigationSystem.h"


UFindPlayerLocation::UFindPlayerLocation()
{
	NodeName = TEXT("Find Player Location");
}

EBTNodeResult::Type UFindPlayerLocation::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	AEnemyController* const AiControl = Cast<AEnemyController>(owner_comp.GetAIOwner());
	APawn* const PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	
	FVector const PlayerPos = PlayerPawn->GetActorLocation();

	if (search_random)
	{
		FNavLocation NavLocation;

		UNavigationSystemV1* const Navsystem = UNavigationSystemV1::GetCurrent(GetWorld());
		if (!Navsystem) { return EBTNodeResult::Failed; }
		if (Navsystem->GetRandomPointInNavigableRadius(PlayerPos, search_range, NavLocation, nullptr))
		{
			AiControl->GetBlackboard()->SetValueAsVector(GetSelectedBlackboardKey(), NavLocation.Location);
		}
	}
	else
	{
		AiControl->GetBlackboard()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPos);
	}

	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}