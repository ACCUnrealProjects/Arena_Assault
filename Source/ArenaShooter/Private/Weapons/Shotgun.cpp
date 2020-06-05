// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Weapons/Shotgun.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

AShotgun::AShotgun()
{
	myWeaponType = GunType::AssultRifle;

	ClipSize = 6;
	MaxAmmo = 36;
	CurrentTotalAmmo = MaxAmmo - ClipSize;
	CurrentClipAmmo = ClipSize;

	DamagePerShot = 20;
	Range = 2000.0f;

	FireRate = 0.7f;
	TotalReloadTime = 1.2f;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>MeshAsset(TEXT("SkeletalMesh'/Game/FirstPerson/FPWeapon/Mesh/SK_FPGun.SK_FPGun'"));
	USkeletalMesh* Asset = MeshAsset.Object;
	GunMesh->SetSkeletalMesh(Asset);
	Muzzle->SetRelativeLocation(FVector(74.999756f, 0.000061f, 10.0f));

	myWeaponType = GunType::ShotGun;
}

void AShotgun::Fire(FVector FirePoint, FRotator FireDirRotator)
{
	ABase_Weapon::Fire(FirePoint, FireDirRotator);

	FHitResult ShotHit;
	FireDirRotator += FRotator(FMath::RandRange(-RecoilCounter, RecoilCounter), FMath::RandRange(-RecoilCounter, RecoilCounter), 0);
	FVector RayEnd = FirePoint + (FireDirRotator.Vector() * Range);

	FCollisionQueryParams ShotParams;
	ShotParams.AddIgnoredActor(this);
	ShotParams.AddIgnoredActor(GunOwner);

	DrawDebugLine(GetWorld(), FirePoint, RayEnd, FColor(255, 0, 0), true, 0, 0, 1);
	if (GetWorld()->LineTraceSingleByChannel(ShotHit, FirePoint, RayEnd, ECollisionChannel::ECC_Camera, ShotParams))
	{
		UGameplayStatics::ApplyDamage(ShotHit.GetActor(), DamagePerShot, Cast<APawn>(GunOwner)->GetController(), GunOwner, UDamageType::StaticClass());
		DrawDebugLine(GetWorld(), FirePoint, ShotHit.ImpactPoint, FColor(0, 255, 0), true, 0, 0, 10);
	}
	CurrentClipAmmo--;
}
