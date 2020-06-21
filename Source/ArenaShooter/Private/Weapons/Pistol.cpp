// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Weapons/Pistol.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

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

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>MeshAsset(TEXT("SkeletalMesh'/Game/MyStuff/Meshes/Pistol/Glock_Rigged.Glock_Rigged'"));
	USkeletalMesh* Asset = MeshAsset.Object;
	GunMesh->SetSkeletalMesh(Asset);
	Muzzle->SetRelativeLocation(FVector(18.0f, 0.0f, 7.0f));
}

void APistol::Fire(FVector FirePoint, FRotator FireDirRotator)
{
	ABase_Weapon::Fire(FirePoint, FireDirRotator);

	FHitResult ShotHit;
	FireDirRotator += FRotator(FMath::RandRange(-RecoilCounter, RecoilCounter), FMath::RandRange(-RecoilCounter, RecoilCounter), 0);
	FVector RayEnd = FirePoint + (FireDirRotator.Vector() * Range);

	FCollisionQueryParams ShotParams;
	ShotParams.AddIgnoredActor(this);
	ShotParams.AddIgnoredActor(GunOwner);

	if (GetWorld()->LineTraceSingleByChannel(ShotHit, FirePoint, RayEnd, ECollisionChannel::ECC_Camera, ShotParams))
	{
		UGameplayStatics::ApplyDamage(ShotHit.GetActor(), DamagePerShot, Cast<APawn>(GunOwner)->GetController(), GunOwner, UDamageType::StaticClass());
		//DrawDebugLine(GetWorld(), FirePoint, ShotHit.ImpactPoint, FColor(0, 255, 0), true, 0, 0, 10);
	}
	CurrentClipAmmo--;
	RecoilCounter = FMath::Clamp<float>(RecoilCounter + 0.05f, 0.1f, MaxRecoilCounter);
}
