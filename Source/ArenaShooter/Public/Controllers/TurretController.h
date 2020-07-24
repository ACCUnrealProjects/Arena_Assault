// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "Perception/AIPerceptionTypes.h"
#include "TurretController.generated.h"

/**
 * 
 */
UCLASS()
class ARENASHOOTER_API ATurretController : public AAIController
{
	GENERATED_BODY()

private:

	UFUNCTION()
	void PawnHasDiedListener();

	virtual void SetPawn(APawn* const InPawn) override;

	virtual void OnPossess(APawn* const InPawn) override;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "AI")
	class UBehaviorTreeComponent* BehaviorTreeComp;

	UPROPERTY(EditInstanceOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"), Category = "AI")
	class UBehaviorTree* BehaviorTree;

	class UBlackboardComponent* BlackBoardComp;

	class UAISenseConfig_Sight* AISightConfig;

	UFUNCTION()
	void OnTargetDetected(AActor* actor, FAIStimulus const stimulus);

	void SetupPerceptionSystem();

protected:

	virtual void BeginPlay() override;

public:

	ATurretController();

	//virtual void Tick(float DeltaTime) override;

	class UBlackboardComponent* GetBlackboard() const;
	
};
