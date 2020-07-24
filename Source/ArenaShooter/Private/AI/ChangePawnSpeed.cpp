// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/AI/ChangePawnSpeed.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"


UChangePawnSpeed::UChangePawnSpeed()
{
	bNotifyBecomeRelevant = true;
	NodeName = TEXT("Change Pawn Speed");
}


void UChangePawnSpeed::OnBecomeRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnBecomeRelevant(OwnerComp, NodeMemory);

	AAIController* const MyAI = Cast<AAIController >(OwnerComp.GetAIOwner());
	if (!MyAI) { return; }
	ACharacter* const MyCharacter = Cast<ACharacter>(MyAI->GetPawn());
	if (!MyCharacter) { return; }
	MyCharacter->GetCharacterMovement()->MaxWalkSpeed = Speed;

}