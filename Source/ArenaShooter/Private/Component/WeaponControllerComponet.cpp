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
	if (MyEquipedGun.Num() > GunOut)
	{
		if (MyEquipedGun[GunOut]->DidIFire(FirePoint, FireDirRotator))
		{
			if (!WeaponAttachSkel) { return; }

			UAnimInstance* AnimInstance = WeaponAttachSkel->GetAnimInstance();
			if (AnimInstance && FireAnimation)
			{
				AnimInstance->Montage_Play(FireAnimation, 1.f);
			}
		}
		else if (MyEquipedGun[GunOut]->OutOfAmmo())
		{
			Reload();
		}
	}
}

void UWeaponControllerComponet::StopFire()
{
	if (MyEquipedGun.Num() > GunOut)
	{
		MyEquipedGun[GunOut]->StopFire();
	}
}

void UWeaponControllerComponet::ChangeGun(int8 WeaponNum)
{
	if (MyEquipedGun.Num() > WeaponNum)
	{
		MyEquipedGun[GunOut]->ChangeActiveState(false);
		GunOut = WeaponNum;
		MyEquipedGun[GunOut]->ChangeActiveState(true);
	}
}

void UWeaponControllerComponet::Reload()
{
	if (MyEquipedGun.Num() > GunOut)
	{
		if (MyEquipedGun[GunOut]->Reload())
		{
			UAnimInstance* AnimInstance = WeaponAttachSkel->GetAnimInstance();
			if (AnimInstance && ReloadAnimation)
			{
				AnimInstance->Montage_Play(ReloadAnimation, 1.f);
			}
		}
	}
}

void UWeaponControllerComponet::AddGun(TSubclassOf<ABase_Weapon> NewWeapon)
{
	if (!NewWeapon) { return; }
	ABase_Weapon* StartGun = GetWorld()->SpawnActor<ABase_Weapon>(NewWeapon, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), SpawnParams);
	if (!StartGun) { return; }
	StartGun->FindComponentByClass<USkeletalMeshComponent>()->AttachToComponent(WeaponAttachSkel, FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), FName(PointInSkel));
	StartGun->OnAttach(GetOwner());
	MyEquipedGun.Add(StartGun);

	if (GunOut != MyEquipedGun.Num() - 1 && MyEquipedGun.Num() > 0)
	{
		MyEquipedGun[GunOut]->ChangeActiveState(false);
		GunOut = MyEquipedGun.Num() - 1;
	}
}

void UWeaponControllerComponet::SetAttachSkel(USkeletalMeshComponent* AttachWeaponTo, FString PointToAttachTo)
{
	WeaponAttachSkel = AttachWeaponTo;
	PointInSkel = PointToAttachTo;
}
