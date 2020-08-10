// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Enemy/Turret.h"
#include "../Public/Component/HealthComponent.h"
#include "../Public/Component/TurretAimingComponent.h"
#include "../Public/MeshComponets/BarrelMesh.h"
#include "../Public/MeshComponets/TurretMesh.h"
#include "../Public/Projectile/TracerRound.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATurret::ATurret()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MyHealthComp= CreateDefaultSubobject<UHealthComponent>(TEXT("MyHealthComponent"));
	MyHealthComp->bEditableWhenInherited = true;
	MyHealthComp->SetMaxHealth(200.0f);

	MyAimingComp = CreateDefaultSubobject<UTurretAimingComponent>(TEXT("MyAimingComponent"));
	MyAimingComp->bEditableWhenInherited = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MyBody"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BodyAsset(TEXT("StaticMesh'/Game/MyStuff/Meshes/Turret/mortar_body.mortar_body'"));
	Body->SetStaticMesh(BodyAsset.Object);
	SetRootComponent(Body);

	MyTurret = CreateDefaultSubobject<UTurretMesh>(TEXT("MyTurret"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> TurretAsset(TEXT("StaticMesh'/Game/MyStuff/Meshes/Turret/mortar_dome.mortar_dome'"));
	MyTurret->SetStaticMesh(TurretAsset.Object);
	MyTurret->AttachToComponent(Body, FAttachmentTransformRules::SnapToTargetIncludingScale, "Turret");

	MyBarrel = CreateDefaultSubobject<UBarrelMesh>(TEXT("MyBarrel"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> BarrelAsset(TEXT("StaticMesh'/Game/MyStuff/Meshes/Turret/mortar_barrel.mortar_barrel'"));
	MyBarrel->SetStaticMesh(BarrelAsset.Object);
	MyBarrel->AttachToComponent(MyTurret, FAttachmentTransformRules::SnapToTargetIncludingScale, "Barrel");

	TurretFireEffect = CreateDefaultSubobject<UParticleSystemComponent>(FName("Fire Effect"));
	TurretFireEffect->AttachToComponent(MyBarrel, FAttachmentTransformRules::KeepRelativeTransform, ("FireLocation"));
	TurretFireEffect->bAutoActivate = false;

	HitEffect = CreateDefaultSubobject<UParticleSystem>(FName("Hit Effect"));
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	MyAimingComp->SetUp(MyTurret, MyBarrel);
	MyHealthComp->IHaveDied.AddUniqueDynamic(this, &ATurret::Death);
	MyHealthComp->IHaveBeenHit.AddUniqueDynamic(this, &ATurret::ImHit);

	MyHealthBar = FindComponentByClass<UWidgetComponent>();
	MyHealthBar->SetVisibleFlag(false);
}

void ATurret::Fire(AActor* Target)
{
	if (!MyAimingComp->CloseToHittingTarget(Target->GetActorLocation()) || !CanFire) { return; }

	FRotator FireDirRotator = MyBarrel->GetSocketRotation(FName("FireLocation"));
	FVector FirePoint = MyBarrel->GetSocketLocation(FName("FireLocation"));

	FHitResult ShotHit;
	FireDirRotator += FRotator(FMath::RandRange(-RecoilMinMax, RecoilMinMax), FMath::RandRange(-RecoilMinMax, RecoilMinMax), 0);
	FVector RayEnd = FirePoint + (FireDirRotator.Vector() * Range);

	FCollisionQueryParams ShotParams;
	ShotParams.AddIgnoredActor(this);

	TurretFireEffect->Activate();

	if (GetWorld()->LineTraceSingleByChannel(ShotHit, FirePoint, RayEnd, ECollisionChannel::ECC_Camera, ShotParams))
	{
		UGameplayStatics::ApplyDamage(ShotHit.GetActor(), Damage, GetController(), this, UDamageType::StaticClass());
		if (HitEffect)
		{
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitEffect, ShotHit.ImpactPoint, ShotHit.ImpactNormal.Rotation());
		}
	}

	if (ProjectileBlueprint)
	{
		GetWorld()->SpawnActor<ATracerRound>(ProjectileBlueprint, MyBarrel->GetSocketLocation(FName("FireLocation")), MyBarrel->GetSocketRotation(FName("FireLocation")));
	}

	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, MyBarrel->GetSocketLocation(FName("FireLocation")));
	}

	CanFire = false;
	FTimerHandle FireTimer;
	GetWorld()->GetTimerManager().SetTimer(FireTimer, this, &ATurret::SetCanFireTrue, FireRate, false);
}

void ATurret::AimAt(AActor* Target)
{
	MyAimingComp->AimToTarget(Target->GetActorLocation());
}

bool ATurret::AmILookingAtTargetDir(FVector Direction)
{
	FVector LocationInDirection = (Direction * 100) + MyTurret->GetComponentLocation();

	MyAimingComp->AimToTarget(LocationInDirection);

	if (MyAimingComp->CloseToHittingTarget(LocationInDirection))
	{
		return true;
	}

	return false;
}

void ATurret::SetCanFireTrue()
{
	CanFire = true;
}

void ATurret::DisableHealthBar()
{
	MyHealthBar->SetVisibleFlag(false);
}

void ATurret::ImHit()
{
	MyHealthBar->SetVisibleFlag(true);
	FTimerHandle HealthUITimer;
	GetWorld()->GetTimerManager().SetTimer(HealthUITimer, this, &ATurret::DisableHealthBar, 5.0f, false);
}

void ATurret::Death()
{
	MyHealthBar->SetVisibleFlag(false);

	if (ExplotionSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, ExplotionSound, GetActorLocation());
	}
	if (HitEffect)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), DeathExplotion, MyTurret->GetComponentLocation(), GetActorRotation());
	}
	Destroy();
}
