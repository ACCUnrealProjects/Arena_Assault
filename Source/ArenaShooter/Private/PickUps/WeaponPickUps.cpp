// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/PickUps/WeaponPickUps.h"
#include "../Public/Component/WeaponControllerComponet.h"
#include "../Public/Weapons/Base_Weapon.h"


AWeaponPickUps::AWeaponPickUps()
{

}

void AWeaponPickUps::TriggerPickUp(class AActor* OtherActor)
{
	UWeaponControllerComponet *ActorsWeaponCon = OtherActor->FindComponentByClass<UWeaponControllerComponet>();
	if (!ActorsWeaponCon) { return; }
	ActorsWeaponCon->AddGun(NewWeapon);
}