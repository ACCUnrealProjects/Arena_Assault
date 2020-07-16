// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Weapons/Pistol.h"

APistol::APistol()
{
	myWeaponType = GunType::Pistol;

	ClipSize = 8;
	MaxAmmo = 64;

	DamagePerShot = 10.0f;
	Range = 5000.0f;

	FireRate = 0.4f;
	TotalReloadTime = 1.5f;

	MaxRecoilCounter = 10;
	RecoilIncrease = 0.05f;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>MeshAsset(TEXT("SkeletalMesh'/Game/MyStuff/Meshes/Pistol/Glock_Rigged.Glock_Rigged'"));
	USkeletalMesh* Asset = MeshAsset.Object;
	GunMesh->SetSkeletalMesh(Asset);
	Muzzle->SetRelativeLocation(FVector(18.0f, 0.0f, 7.0f));
}

