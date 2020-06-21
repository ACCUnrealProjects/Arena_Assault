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
}


// Called when the game starts
void UWeaponControllerComponet::BeginPlay()
{
	Super::BeginPlay();

	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = Cast<APawn>(GetOwner());	
}

// Called every frame
void UWeaponControllerComponet::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UWeaponControllerComponet::FireCurrentWeapon(FVector FirePoint, FRotator FireDirRotator)
{
	if (CurrentWeapon != nullptr)
	{
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
}

void UWeaponControllerComponet::StopFire()
{
	if (CurrentWeapon == nullptr) { return; }
	CurrentWeapon->StopFire();
}

void UWeaponControllerComponet::ChangeGun(int8 WeaponNum)
{
	if (MyEquipedGuns.Num() < 0 || WeaponNum > MyEquipedGuns.Num() - 1) { return; }
	if (CurrentWeapon == MyEquipedGuns[WeaponNum]) { return; }

	UAnimInstance* AnimInstance = WeaponAttachSkel->GetAnimInstance();
	AnimInstance->Montage_Stop(0.0f);

	CurrentWeapon->ChangeActiveState(false);
	CurrentWeapon = MyEquipedGuns[WeaponNum];
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

void UWeaponControllerComponet::AddGun(TSubclassOf<ABase_Weapon> NewWeapon)
{
	if (!NewWeapon) { return; }
	ABase_Weapon* NewGun = GetWorld()->SpawnActor<ABase_Weapon>(NewWeapon, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), SpawnParams);
	if (!NewGun) { return; }
	NewGun->FindComponentByClass<USkeletalMeshComponent>()->AttachToComponent(WeaponAttachSkel, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), FName(PointInSkel));
	NewGun->OnAttach(GetOwner());
	MyEquipedGuns.Emplace(NewGun);
	if (CurrentWeapon != nullptr && MyEquipedGuns.Num() > 0)
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
	for (auto Gun : MyEquipedGuns)
	{
		if (Gun->GetGunType() == NewGunType)
		{
			return true;
		}
	}
	return false;
}

ABase_Weapon* UWeaponControllerComponet::GetCurrentGun()
{
	return CurrentWeapon;
}