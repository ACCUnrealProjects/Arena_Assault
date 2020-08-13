// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/PickUps/HealthPickup.h"
#include "../Public/Component/HealthComponent.h"

bool AHealthPickup::TriggerPickUp(AActor* OtherActor)
{
	UHealthComponent* ActorsHealthComp = OtherActor->FindComponentByClass<UHealthComponent>();
	if (!ActorsHealthComp) { return false; }
	if (ActorsHealthComp->AmIAtMaxHealth()) { return false; }
	ActorsHealthComp->IncreaseHealth(HealthAmmount);
	return true;
}

