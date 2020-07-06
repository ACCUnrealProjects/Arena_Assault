// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Weapons/Assult_Rifle.h"
#include "Kismet/GameplayStatics.h"

AAssult_Rifle::AAssult_Rifle()
{
	myWeaponType = GunType::AssultRifle;

	ClipSize = 30;
	MaxAmmo = 180;

	DamagePerShot = 17;
	Range = 8000.0f;

	FireRate = 0.2f;
	TotalReloadTime = 2.0f;

	MaxRecoilCounter = 10;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>MeshAsset(TEXT("SkeletalMesh'/Game/MyStuff/Meshes/AK/AK_rigged.AK_rigged'"));
	USkeletalMesh* Asset = MeshAsset.Object;
	GunMesh->SetSkeletalMesh(Asset);
	Muzzle->SetRelativeLocation(FVector(75.0f, 0.0f, 10.0f));
}

void AAssult_Rifle::Fire(FVector FirePoint, FRotator FireDirRotator)
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
	RecoilCounter = FMath::Clamp<float>(RecoilCounter + 0.2f, 0.1f, MaxRecoilCounter);
}
