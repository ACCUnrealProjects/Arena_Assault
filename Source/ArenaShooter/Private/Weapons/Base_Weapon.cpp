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

	if (CurrentClipAmmo > 0)
	{
		if (GetWorld()->GetRealTimeSeconds() - LastFire >= FireRate)
		{
			myWeaponState = WeaponState::Fireing;
			Fire(FirePoint, FireDirRotator);
			LastFire = GetWorld()->GetRealTimeSeconds();
			return true;
		}
	}

	return false;
}

void ABase_Weapon::ChangeActiveState(bool state)
{
	SetActorHiddenInGame(state);

	SetActorEnableCollision(state);

	SetActorTickEnabled(state);

	myWeaponState = WeaponState::Idle;
}


bool ABase_Weapon::OutOfAmmo()
{
	return CurrentClipAmmo == 0;
}

GunType ABase_Weapon::GetGunType()
{
	return myWeaponType;
}