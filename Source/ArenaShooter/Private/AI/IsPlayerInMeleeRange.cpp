// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/AI/IsPlayerInMeleeRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "../Public/Controllers/ZombieAIController.h"


UIsPlayerInMeleeRange::UIsPlayerInMeleeRange()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Player In Melee Range");
}

void UIsPlayerInMeleeRange::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	auto const AiControl = Cast<AZombieAIController>(OwnerComp.GetAIOwner());
	auto const Zombie = AiControl->GetPawn();

	auto const PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();

	AiControl->GetBlackboard()->SetValueAsBool(GetSelectedBlackboardKey(), Zombie->GetDistanceTo(PlayerPawn) <= MeleeRange);
}