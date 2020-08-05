// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Weapons/RayGun.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

ARayGun::ARayGun()
{
	myWeaponType = GunType::RayGun;

	ClipSize = 1;
	MaxAmmo = 30;

	FireRate = 1.0f;
	TotalReloadTime = 1.0f;

	DamagePerShot = 100;
	Range = 10000.0f;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>MeshAsset(TEXT("SkeletalMesh'/Game/FirstPerson/FPWeapon/Mesh/SK_FPGun.SK_FPGun'"));
	GunMesh->SetSkeletalMesh(MeshAsset.Object);
	Muzzle->SetRelativeLocation(FVector(0.0f, 55.0f, 10.0f));

	FParticleSysParam Source;
	Source.Name = "Source";
	Source.ParamType = EParticleSysParamType::PSPT_Vector;
	Source.Vector = Muzzle->GetComponentLocation();
	FireEffect->InstanceParameters.Add(Source);

	FParticleSysParam Target;
	Target.Name = "Target";
	Target.ParamType = EParticleSysParamType::PSPT_Vector;
	Target.Vector = Muzzle->GetComponentLocation();
	FireEffect->InstanceParameters.Add(Target);

	FireEffect->SetBeamSourcePoint(0, Muzzle->GetComponentLocation(), 0);
	FireEffect->SetBeamEndPoint(0, Muzzle->GetComponentLocation());
}

void ARayGun::Fire(FVector FirePoint, FRotator FireDirRotator)
{
	ABase_Weapon::Fire(FirePoint, FireDirRotator);

	TArray<FHitResult> ShotHits;
	FVector RayEnd = FirePoint + (FireDirRotator.Vector() * Range);

	FCollisionQueryParams ShotParams;
	ShotParams.AddIgnoredActor(this);
	ShotParams.AddIgnoredActor(GunOwner);

	FCollisionObjectQueryParams WhatToHit;
	WhatToHit.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldStatic);
	WhatToHit.AddObjectTypesToQuery(ECollisionChannel::ECC_WorldDynamic);
	WhatToHit.AddObjectTypesToQuery(ECollisionChannel::ECC_PhysicsBody);

	FVector LastHitPos = RayEnd;
	if (GetWorld()->LineTraceMultiByObjectType(ShotHits, FirePoint, RayEnd, WhatToHit, ShotParams))
	{
		for (int32 i = 0; i < ShotHits.Num(); i++)
		{
			UGameplayStatics::ApplyDamage(ShotHits[i].GetActor(), DamagePerShot, Cast<APawn>(GunOwner)->GetController(), GunOwner, UDamageType::StaticClass());
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, ShotHits[i].ImpactPoint, ShotHits[i].ImpactNormal.Rotation());
			LastHitPos = ShotHits[i].ImpactPoint;
			if (ShotHits[i].GetComponent() && ShotHits[i].GetComponent()->GetCollisionObjectType() == ECollisionChannel::ECC_WorldStatic)
			{
				break;
			}
		}
	}
	CurrentClipAmmo--;

	FireEffect->SetVectorParameter("Source", Muzzle->GetComponentLocation());
	FireEffect->SetVectorParameter("Target", LastHitPos);
	FireEffect->SetBeamSourcePoint(0, Muzzle->GetComponentLocation(), 0);
	FireEffect->SetBeamEndPoint(0, LastHitPos);
	FTimerHandle Temp;
	GetWorld()->GetTimerManager().SetTimer(Temp, this, &ARayGun::DeActivateLaser, 0.1f, false);
}

void ARayGun::OnAttach(AActor* MyOwner)
{
	ABase_Weapon::OnAttach(MyOwner);
	AddActorLocalRotation(FRotator(0.0f, -90.0f, 0.0f));
}


void ARayGun::DeActivateLaser()
{
	if (FireEffect)
	{
		FireEffect->Deactivate();
	}
}