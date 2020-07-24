// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Weapons/Single_Bullet_Fire.h"
#include "../Public/Projectile/TracerRound.h"
#include "Kismet/GameplayStatics.h"


ASingle_Bullet_Fire::ASingle_Bullet_Fire()
{
	RecoilCounter = 0;
}

void ASingle_Bullet_Fire::Fire(FVector FirePoint, FRotator FireDirRotator)
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
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, ShotHit.ImpactPoint, ShotHit.ImpactNormal.Rotation());
	}
	CurrentClipAmmo--;
	RecoilCounter = FMath::Clamp<float>(RecoilCounter + RecoilIncrease, 0.1f, MaxRecoilCounter);

	if (ProjectileBlueprint)
	{
		GetWorld()->SpawnActor<ATracerRound>(ProjectileBlueprint, Muzzle->GetComponentLocation(), FireDirRotator);
	}
}

bool ASingle_Bullet_Fire::Reload()
{
	RecoilCounter = 0;
	return ABase_Weapon::Reload();
}

void ASingle_Bullet_Fire::StopFire()
{
	RecoilCounter = 0;
	ABase_Weapon::StopFire();
}
