// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Controllers/ZombieAIController.h"
#include "../Public/Component/HealthComponent.h"
#include "../Public/Enemy/Zombie.h"
#include "GameFramework/Character.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AIPerceptionComponent.h"

AZombieAIController::AZombieAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> obj(TEXT("BehaviorTree'/Game/MyStuff/AI/Zombie_AI_BT.Zombie_AI_BT'"));
	if (obj.Succeeded())
	{
		BehaviorTree = obj.Object;
	}
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorTreeComp"));
	BlackBoardComp = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackboardComp"));
	SetupPerceptionSystem();

}

void AZombieAIController::OnTargetDetected(AActor* actor, FAIStimulus const stimulus)
{
	if (actor && actor == Cast<AActor>(GetWorld()->GetFirstPlayerController()->GetPawn()))
	{
		GetBlackboard()->SetValueAsBool(TEXT("CanSeePlayer"), stimulus.WasSuccessfullySensed());
	}
}

void AZombieAIController::SetupPerceptionSystem()
{
	AISightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("AI Sight"));
	SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception Comp")));
	AISightConfig->SightRadius = 500.0f;
	AISightConfig->LoseSightRadius = AISightConfig->SightRadius * 1.1f;
	AISightConfig->PeripheralVisionAngleDegrees = 90.0f;
	AISightConfig->SetMaxAge(5.0f);
	AISightConfig->AutoSuccessRangeFromLastSeenLocation = 900.0f;
	AISightConfig->DetectionByAffiliation.bDetectEnemies = true;
	AISightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	AISightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	GetPerceptionComponent()->SetDominantSense(*AISightConfig->GetSenseImplementation());
	GetPerceptionComponent()->OnTargetPerceptionUpdated.AddDynamic(this, &AZombieAIController::OnTargetDetected);
	GetPerceptionComponent()->ConfigureSense(*AISightConfig);
}

void AZombieAIController::BeginPlay()
{
	Super::BeginPlay();
	RunBehaviorTree(BehaviorTree);
	BehaviorTreeComp->StartTree(*BehaviorTree);
}

void AZombieAIController::OnPossess(APawn* const InPawn)
{
	Super::OnPossess(InPawn);
	if (BlackBoardComp)
	{
		BlackBoardComp->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	}
}

void AZombieAIController::SetPawn(APawn* const InPawn)
{
	Super::SetPawn(InPawn);

	if (InPawn)
	{
		UHealthComponent* PawnsHealthCon = InPawn->FindComponentByClass<UHealthComponent>();
		if (!ensure(PawnsHealthCon)) { return; }
		PawnsHealthCon->IHaveDied.AddUniqueDynamic(this, &AZombieAIController::PawnHasDiedListener);
	}
}

void AZombieAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AZombieAIController::PawnHasDiedListener()
{
	if (!GetPawn()) { return; }
	GetPawn()->Destroy();
}

UBlackboardComponent* AZombieAIController::GetBlackboard() const
{
	return BlackBoardComp;
}

