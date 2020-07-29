// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/AI/IsTargetInMeleeRange.h"
#include "../Public/Controllers/EnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "GameFramework/Character.h"

UIsTargetInMeleeRange::UIsTargetInMeleeRange()
{
	bNotifyTick = true;
	NodeName = TEXT("Target In Melee Range");
}

void UIsTargetInMeleeRange::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AEnemyController* const MyZombieAI = Cast<AEnemyController>(OwnerComp.GetAIOwner());
	APawn* const Zombie = MyZombieAI->GetPawn();

	AActor* const TargetActor = Cast<AActor>(MyZombieAI->GetBlackboard()->GetValueAsObject(GetSelectedBlackboardKey()));

	bool TargetInMelee = Zombie->GetDistanceTo(TargetActor) <= MeleeRange;

	MyZombieAI->GetBlackboard()->SetValueAsBool(InRangeBool.SelectedKeyName, TargetInMelee);
}
