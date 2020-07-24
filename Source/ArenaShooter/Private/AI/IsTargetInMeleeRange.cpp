// Fill out your copyright notice in the Description page of Project Settings.


#include "..\..\Public\AI\IsTargetInMeleeRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "GameFramework/Character.h"
#include "../Public/Controllers/ZombieAIController.h"

UIsTargetInMeleeRange::UIsTargetInMeleeRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Target In Melee Range");
}

void UIsTargetInMeleeRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	AZombieAIController* const MyZombieAI = Cast<AZombieAIController>(OwnerComp.GetAIOwner());
	APawn* const Zombie = MyZombieAI->GetPawn();

	AActor* const TargetActor = Cast<AActor>(MyZombieAI->GetBlackboard()->GetValueAsObject(GetSelectedBlackboardKey()));

	MyZombieAI->GetBlackboard()->SetValueAsBool(InRangeBool.SelectedKeyName, Zombie->GetDistanceTo(TargetActor) <= MeleeRange);
}
