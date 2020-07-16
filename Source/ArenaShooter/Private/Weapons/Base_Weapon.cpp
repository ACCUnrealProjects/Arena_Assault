#include "../Public/Weapons/Base_Weapon.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABase_Weapon::ABase_Weapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	GunMesh->CastShadow = false;
	GunMesh->bCastDynamicShadow = false;
	SetRootComponent(GunMesh);


	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(GunMesh);

	FireEffect = CreateDefaultSubobject<UParticleSystemComponent>(FName("Fire Effect"));
	FireEffect->AttachToComponent(Muzzle, FAttachmentTransformRules::KeepRelativeTransform);
	FireEffect->bAutoActivate = false;

	HitEffect = CreateDefaultSubobject<UParticleSystem>(FName("Hit Effect"));
}

void ABase_Weapon::BeginPlay()
{
	Super::BeginPlay();

	CurrentTotalAmmo = MaxAmmo - ClipSize;
	CurrentClipAmmo = ClipSize;
}

void ABase_Weapon::Fire(FVector FirePoint, FRotator FireDirRotator)
{
	if (FireAnimation)
	{
		GunMesh->PlayAnimation(FireAnimation,false);
	}
	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
	FireEffect->Activate();
}

bool ABase_Weapon::Reload()
{
	if (CurrentClipAmmo == ClipSize || CurrentTotalAmmo == 0 || myWeaponState == WeaponState::Reloading) { return false; }

	myWeaponState = WeaponState::Reloading;
	if (ReloadAnimation)
	{
		GunMesh->PlayAnimation(ReloadAnimation, false);
	}
	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ABase_Weapon::ReloadComplete, TotalReloadTime, false);
	return true;
}

void ABase_Weapon::ReloadComplete()
{
	myWeaponState = WeaponState::Idle;
	int32 BulletsWeCanAdd = 0;
	int32 WantedBullets = ClipSize - CurrentClipAmmo;
	BulletsWeCanAdd = FMath::Min(CurrentTotalAmmo, WantedBullets);
	CurrentClipAmmo = CurrentClipAmmo + BulletsWeCanAdd;
	CurrentTotalAmmo -= BulletsWeCanAdd;
}

void ABase_Weapon::OnAttach(AActor* MyOwner)
{
	GunOwner = MyOwner;
}

void ABase_Weapon::StopFire()
{
	if (myWeaponState != WeaponState::Reloading)
	{
		myWeaponState = WeaponState::Idle;
	}
}

bool ABase_Weapon::DidIFire(FVector FirePoint, FRotator FireDirRotator)
{
	if (myWeaponState == WeaponState::Reloading) { return false; }

	if (GetWorld()->GetRealTimeSeconds() - LastFire >= FireRate)
	{
		LastFire = GetWorld()->GetRealTimeSeconds();
		if (CurrentClipAmmo <= 0 && CurrentTotalAmmo <= 0)
		{
			if (DryClipSound)
			{
				UGameplayStatics::PlaySoundAtLocation(this, DryClipSound, GetActorLocation());
			}
			return false;
		}
		else if(CurrentClipAmmo > 0)
		{
			myWeaponState = WeaponState::Fireing;
			Fire(FirePoint, FireDirRotator);
			return true;
		}
	}

	return false;
}

void ABase_Weapon::ChangeActiveState(const bool AmIActive)
{
	GetWorld()->GetTimerManager().ClearTimer(ReloadTimer);

	myWeaponState = WeaponState::Idle;

	SetActorHiddenInGame(!AmIActive);

	SetActorEnableCollision(AmIActive);
}

bool ABase_Weapon::OutOfAmmo() const
{
	return CurrentClipAmmo <= 0;
}

void ABase_Weapon::AddAmmo(const int32 Ammo)
{
	CurrentTotalAmmo = FMath::Min(CurrentTotalAmmo + Ammo, MaxAmmo);
}

GunType ABase_Weapon::GetGunType() const
{
	return myWeaponType;
}