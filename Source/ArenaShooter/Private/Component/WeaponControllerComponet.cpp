// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Component/WeaponControllerComponet.h"
#include "../Public/Weapons/Base_Weapon.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWeaponControllerComponet::UWeaponControllerComponet()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	GunSlots.Add(GunType::Pistol);
	GunSlots.Add(GunType::AssultRifle);
	GunSlots.Add(GunType::RayGun);

	MyGuns.Init(nullptr, GunSlots.Num());
}


// Called when the game starts
void UWeaponControllerComponet::BeginPlay()
{
	Super::BeginPlay();

	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = Cast<APawn>(GetOwner());	
}

void UWeaponControllerComponet::FireCurrentWeapon(FVector FirePoint, FRotator FireDirRotator)
{
	if (CurrentWeapon == nullptr) { return; }

	if (CurrentWeapon->DidIFire(FirePoint, FireDirRotator))
	{
		if (!WeaponAttachSkel) { return; }

		UAnimInstance* AnimInstance = WeaponAttachSkel->GetAnimInstance();
		GunType MyGunType = CurrentWeapon->GetGunType();
		if (AnimInstance && FireAnimations[MyGunType])
		{
			AnimInstance->Montage_Play(FireAnimations[MyGunType]);
		}
	}
	else if (CurrentWeapon->OutOfAmmo())
	{
		Reload();
	}
}

void UWeaponControllerComponet::StopFire()
{
	if (CurrentWeapon == nullptr) { return; }
	CurrentWeapon->StopFire();
}

void UWeaponControllerComponet::ChangeGun(GunType SwitchGunType)
{
	int GunSlot = 0;
	for (int i = 0; i < GunSlots.Num(); i++)
	{
		if (GunSlots[i] == SwitchGunType)
		{
			GunSlot = i;
			break;
		}
	}

	if (CurrentWeapon == MyGuns[GunSlot] || MyGuns[GunSlot] == nullptr) { return; }

	UAnimInstance* AnimInstance = WeaponAttachSkel->GetAnimInstance();
	AnimInstance->Montage_Stop(0.0f);

	CurrentWeapon->ChangeActiveState(false);
	CurrentWeapon = MyGuns[GunSlot];
	CurrentWeapon->ChangeActiveState(true);
}

void UWeaponControllerComponet::Reload()
{
	if (CurrentWeapon != nullptr)
	{
		if (CurrentWeapon->Reload())
		{
			UAnimInstance* AnimInstance = WeaponAttachSkel->GetAnimInstance();
			GunType MyGunType = CurrentWeapon->GetGunType();
			if (AnimInstance && ReloadAnimations[MyGunType])
			{
				AnimInstance->Montage_Play(ReloadAnimations[MyGunType]);
			}
		}
	}
}

void UWeaponControllerComponet::AddGun(TSubclassOf<ABase_Weapon> NewWeapon, GunType myWeaponType)
{
	if (!NewWeapon) { return; }
	ABase_Weapon* NewGun = GetWorld()->SpawnActor<ABase_Weapon>(NewWeapon, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), SpawnParams);
	if (!NewGun) { return; }
	NewGun->FindComponentByClass<USkeletalMeshComponent>()->AttachToComponent(WeaponAttachSkel, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), FName(PointInSkel));
	NewGun->OnAttach(GetOwner());
	int GunSlot = 0;
	for (int i = 0; i < GunSlots.Num(); i++)
	{
		if (GunSlots[i] == myWeaponType)
		{
			GunSlot = i;
			break;
		}
	}
	MyGuns[GunSlot] = NewGun;
	if (CurrentWeapon != nullptr)
	{
		CurrentWeapon->ChangeActiveState(false);
	}
	CurrentWeapon = NewGun;
}

void UWeaponControllerComponet::SetAttachSkel(USkeletalMeshComponent* AttachWeaponTo, FString PointToAttachTo)
{
	WeaponAttachSkel = AttachWeaponTo;
	PointInSkel = PointToAttachTo;
}

bool UWeaponControllerComponet::DoIAlreadyHaveGun(GunType NewGunType)
{
	for (int i = 0; i < GunSlots.Num(); i++)
	{
		if (GunSlots[i] == NewGunType)
		{
			if (MyGuns[i] != nullptr) { return true; }
			else { return false; }
		}
	}
	return false;
}

ABase_Weapon* UWeaponControllerComponet::GetCurrentGun()
{
	return CurrentWeapon;
}