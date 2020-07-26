// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/AI/LookForPlayerTarget.h"
#include "../Public/Controllers/EnemyController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

ULookForPlayerTarget::ULookForPlayerTarget()
{
	bNotifyTick = true;
	NodeName = TEXT("Look For Player Traget");
}


void ULookForPlayerTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AEnemyController* const MyAI = Cast<AEnemyController >(OwnerComp.GetAIOwner());
	if (!MyAI) { return; }
	ACharacter* const MyCharacter = Cast<ACharacter>(MyAI->GetPawn());
	if (!MyCharacter) { return; }

	auto const PlayerExists = GetWorld()->GetFirstPlayerController();

	bool SeePlayer = MyAI->GetBlackboard()->GetValueAsBool(CanSeePlayerBool.SelectedKeyName);
	auto const TargetActor = MyAI->GetBlackboard()->GetValueAsObject(GetSelectedBlackboardKey());

	if (SeePlayer && !TargetActor)
	{
		MyAI->GetBlackboard()->SetValueAsObject(GetSelectedBlackboardKey(), PlayerExists->GetPawn());
		MyCharacter->GetCharacterMovement()->MaxWalkSpeed = FoundSpeed;
	}
	else if ((!SeePlayer && TargetActor))
	{
		MyAI->GetBlackboard()->SetValueAsObject(GetSelectedBlackboardKey(), nullptr);
		MyCharacter->GetCharacterMovement()->MaxWalkSpeed = LostSpeed;
	}
	else if (!PlayerExists || !PlayerExists->GetPawn())
	{
		MyCharacter->GetCharacterMovement()->MaxWalkSpeed = LostSpeed;
	}

}
