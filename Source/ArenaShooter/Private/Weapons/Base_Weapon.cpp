#include "../Public/Weapons/Base_Weapon.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABase_Weapon::ABase_Weapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	GunMesh->CastShadow = false;
	GunMesh->bCastDynamicShadow = false;
	SetRootComponent(GunMesh);

	RecoilCounter = 0;

	Muzzle = CreateDefaultSubobject<USceneComponent>(TEXT("Muzzle"));
	Muzzle->SetupAttachment(GunMesh);

	FireEffect = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FireEffect"));
	FireEffect->SetupAttachment(Muzzle);
	FireEffect->SetVisibility(false);
	FireEffect->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	FireEffect->CastShadow = false;
}

void ABase_Weapon::BeginPlay()
{
	Super::BeginPlay();

	CurrentTotalAmmo = MaxAmmo - ClipSize;
	CurrentClipAmmo = ClipSize;
}

// Called every frame
void ABase_Weapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (myWeaponState == WeaponState::Reloading)
	{
		if (GetWorld()->GetRealTimeSeconds() - ReloadStartTime >= TotalReloadTime)
		{
			myWeaponState = WeaponState::Idle;
			int32 BulletsToAdd = ClipSize - CurrentClipAmmo;
			int32 NewClip = FMath::Clamp<uint32>(ClipSize, 0, FMath::Min(ClipSize, CurrentTotalAmmo));
			CurrentClipAmmo = NewClip;
			CurrentTotalAmmo -= BulletsToAdd;
		}
	}
}

void ABase_Weapon::Fire(FVector FirePoint, FRotator FireDirRotator)
{
	if (FireAnimation)
	{
		GunMesh->PlayAnimation(FireAnimation,false);
		float FlashScale = FMath::RandRange(0.2f, 0.3f);
		FireEffect->SetWorldScale3D(FVector(FlashScale, FlashScale, FlashScale));
		FireEffect->SetVisibility(true);
		FTimerHandle Timer;
		GetWorld()->GetTimerManager().SetTimer(Timer, this, &ABase_Weapon::DeSpawnFireEffect, 0.1f, false);
	}

	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(this, FireSound, GetActorLocation());
	}
}

bool ABase_Weapon::Reload()
{
	if (CurrentClipAmmo == ClipSize || CurrentTotalAmmo == 0 || myWeaponState == WeaponState::Reloading) { return false; }

	myWeaponState = WeaponState::Reloading;
	RecoilCounter = 0;
	ReloadStartTime = GetWorld()->GetRealTimeSeconds();
	if (ReloadAnimation)
	{
		GunMesh->PlayAnimation(ReloadAnimation, false);
	}
	return true;
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
	RecoilCounter = 0;
}

bool ABase_Weapon::DidIFire(FVector FirePoint, FRotator FireDirRotator)
{
	if (myWeaponState == WeaponState::Reloading)
	{
		return false;
	}

	if (GetWorld()->GetRealTimeSeconds() - LastFire >= FireRate)
	{
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
			LastFire = GetWorld()->GetRealTimeSeconds();
			return true;
		}

	}
	return false;
}

void ABase_Weapon::ChangeActiveState(bool AmIActive)
{
	SetActorHiddenInGame(!AmIActive);

	SetActorEnableCollision(AmIActive);

	SetActorTickEnabled(AmIActive);

	myWeaponState = WeaponState::Idle;
}


bool ABase_Weapon::OutOfAmmo()
{
	return CurrentClipAmmo <= 0;
}

void ABase_Weapon::DeSpawnFireEffect()
{
	FireEffect->SetVisibility(false);
}

GunType ABase_Weapon::GetGunType()
{
	return myWeaponType;
}