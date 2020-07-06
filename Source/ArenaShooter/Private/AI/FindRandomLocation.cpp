// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/AI/FindRandomLocation.h"
#include "../Public/Controllers/ZombieAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyType_Vector.h"
#include "NavigationSystem.h"

UFindRandomLocation::UFindRandomLocation()
{
    NodeName = TEXT("Find Random Location");
}

EBTNodeResult::Type UFindRandomLocation::ExecuteTask(UBehaviorTreeComponent& owner_comp, uint8* node_memory)
{
    auto const AiControl = Cast<AZombieAIController>(owner_comp.GetAIOwner());
    auto const Zombie = AiControl->GetPawn();

    FVector const GetCurrentPos = Zombie->GetActorLocation();
    FNavLocation NewLocationSearch;

    UNavigationSystemV1* const WorldNavSys = UNavigationSystemV1::GetCurrent(GetWorld());
    if (!WorldNavSys) { return EBTNodeResult::Failed; }


    if (WorldNavSys->GetRandomPointInNavigableRadius(GetCurrentPos, Radius, NewLocationSearch, nullptr))
    {
        AiControl->GetBlackboard()->SetValueAsVector(GetSelectedBlackboardKey(), NewLocationSearch.Location);
    }

    FinishLatentTask(owner_comp, EBTNodeResult::Succeeded);

    return EBTNodeResult::Succeeded;
}
