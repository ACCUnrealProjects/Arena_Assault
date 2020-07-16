// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Weapons/Assult_Rifle.h"

AAssult_Rifle::AAssult_Rifle()
{
	myWeaponType = GunType::AssultRifle;

	ClipSize = 30;
	MaxAmmo = 180;

	DamagePerShot = 17;
	Range = 8000.0f;

	FireRate = 0.2f;
	TotalReloadTime = 2.0f;
	RecoilIncrease = 0.2f;

	MaxRecoilCounter = 10;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>MeshAsset(TEXT("SkeletalMesh'/Game/MyStuff/Meshes/AK/AK_rigged.AK_rigged'"));
	USkeletalMesh* Asset = MeshAsset.Object;
	GunMesh->SetSkeletalMesh(Asset);

	Muzzle->SetRelativeLocation(FVector(75.0f, 0.0f, 10.0f));
}
