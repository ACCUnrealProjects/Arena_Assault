// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/AI/MeleeAttack.h"
#include "../Public/Controllers/ZombieAIController.h"
#include "../Public/Enemy/Zombie.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"

UMeleeAttack::UMeleeAttack()
{
	NodeName = TEXT("Melee Attack");

}

EBTNodeResult::Type UMeleeAttack::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
	auto const AiControl = Cast<AZombieAIController>(owner_comp.GetAIOwner());
	auto const Zombie = Cast<AZombie>(AiControl->GetPawn());

	AActor* TargetActor = Cast<AActor>(AiControl->GetBlackboard()->GetValueAsObject(GetSelectedBlackboardKey()));

	if (Zombie && TargetActor)
	{
		Zombie->MeleeAttack(TargetActor);
	}

	FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);

	return EBTNodeResult::Succeeded;
}