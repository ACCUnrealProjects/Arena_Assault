// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/AI/ChangeCharacterSpeed.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/BehaviorTreeTypes.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UChangeCharacterSpeed::UChangeCharacterSpeed()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Change Character Speed");
}

void UChangeCharacterSpeed::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	AAIController* const MyAI = Cast<AAIController>(OwnerComp.GetAIOwner());
	if (!MyAI) { return; }
	ACharacter* const MyCharacter = Cast<ACharacter>(MyAI->GetPawn());
	if (!MyCharacter || !MyCharacter->GetCharacterMovement()) { return; }

	MyCharacter->GetCharacterMovement()->MaxWalkSpeed = Speed;
}
