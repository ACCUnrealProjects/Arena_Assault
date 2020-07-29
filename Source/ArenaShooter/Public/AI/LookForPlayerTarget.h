// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "LookForPlayerTarget.generated.h"

/**
 * 
 */
UCLASS()
class ARENASHOOTER_API ULookForPlayerTarget : public UBTService_BlackboardBase
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere, Category = "Blackboard", meta = (AllowPrivateAccess = "true"))
	struct FBlackboardKeySelector CanSeePlayerBool;

public:

	ULookForPlayerTarget();

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

};
