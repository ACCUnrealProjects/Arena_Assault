// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/PickUps/AmmoPickUps.h"
#include "../Public/Component/WeaponControllerComponet.h"

AAmmoPickUps::AAmmoPickUps()
{

}

bool AAmmoPickUps::TriggerPickUp(class AActor* OtherActor)
{
	UWeaponControllerComponet* ActorsWeaponCon = OtherActor->FindComponentByClass<UWeaponControllerComponet>();
	if (!ActorsWeaponCon) { return false; }
	return ActorsWeaponCon->TryAndAddAmmoForGun(myWeaponType, AmmoAmmount);
}