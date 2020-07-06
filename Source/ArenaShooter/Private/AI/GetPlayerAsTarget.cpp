// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/AI/GetPlayerAsTarget.h"
#include "../Public/Controllers/ZombieAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"

UGetPlayerAsTarget::UGetPlayerAsTarget()
{
	NodeName = TEXT("Get Player Target");
}

EBTNodeResult::Type UGetPlayerAsTarget::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	AZombieAIController* const AiControl = Cast<AZombieAIController>(owner_comp.GetAIOwner());

	auto const PlayerExists = GetWorld()->GetFirstPlayerController();

	if (!PlayerExists || !PlayerExists->GetPawn()) { return EBTNodeResult::Succeeded; }

	AActor* const PlayerActor = Cast<AActor>(PlayerExists->GetPawn());

	AiControl->GetBlackboard()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerActor);

	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}