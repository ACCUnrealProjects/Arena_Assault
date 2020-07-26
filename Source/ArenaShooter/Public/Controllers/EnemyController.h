// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "EnemyController.generated.h"

/**
 * 
 */
UCLASS()
class ARENASHOOTER_API AEnemyController : public AAIController
{
	GENERATED_BODY()

private:

protected:

	virtual void BeginPlay() override;

	virtual void SetPawn(APawn* const InPawn) override;

	virtual void OnPossess(APawn* const InPawn) override;

	virtual void SetupPerceptionSystem();

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "AI")
	class UBehaviorTreeComponent* BehaviorTreeComp;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "AI")
	class UBehaviorTree* BehaviorTree;

	class UBlackboardComponent* BlackBoardComp;

	class UAISenseConfig_Sight* AISightConfig;

public:

	AEnemyController();

	class UBlackboardComponent* GetBlackboard() const;
	
};
