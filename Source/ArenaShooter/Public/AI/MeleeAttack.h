// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "MeleeAttack.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ARENASHOOTER_API UMeleeAttack : public UBTTask_BlackboardBase
{
	GENERATED_BODY()

private:

protected:

public:
	UMeleeAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory) override;

};
