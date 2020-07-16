// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Character/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/CapsuleComponent.h"
#include "Materials/MaterialParameterCollectionInstance.h"
#include "Kismet/GameplayStatics.h"
#include "../Public/Weapons/Base_Weapon.h"
#include "../Public/Component/HealthComponent.h"
#include "../Public/Component/WeaponControllerComponet.h"
#include "../Public/Component/CharacterDashComponent.h"
#include "../Public/Component/GrappleControlComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCapsuleSize(55.f, 90.0f);

	WallRunCap = CreateDefaultSubobject<UCapsuleComponent>(TEXT("WallRunCapsule"));
	WallRunCap->SetCapsuleSize(60.0f, 90.0f);
	WallRunCap->SetGenerateOverlapEvents(true);
	WallRunCap->SetupAttachment(GetCapsuleComponent());

	MyCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FirstPersonCamera"));
	MyCamera->SetupAttachment(GetCapsuleComponent());
	MyCamera->SetRelativeLocation(FVector(-22.0f, -10.0f, 30.0f));
	MyCamera->bUsePawnControlRotation = true;

	MyMoveComp = FindComponentByClass<UCharacterMovementComponent>();

	static ConstructorHelpers::FObjectFinder<USkeletalMesh>MeshAsset(TEXT("SkeletalMesh'/Game/MyStuff/Meshes/Arms/FPSArms_rigged.FPSArms_rigged'"));
	SM_Arms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("CharacterMesh1P"));
	SM_Arms->SetSkeletalMesh(MeshAsset.Object);
	SM_Arms->SetOnlyOwnerSee(true);
	SM_Arms->SetupAttachment(MyCamera);
	SM_Arms->bCastDynamicShadow = false;
	SM_Arms->CastShadow = false;
	SM_Arms->SetRelativeLocation(FVector(0.f, 10.0f, -20.0f));
	
	MyWeaponController = CreateDefaultSubobject<UWeaponControllerComponet>(TEXT("MyWeaponComponent"));
	MyWeaponController->bEditableWhenInherited = true;

	MyHealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("MyHealthComponent"));
	MyHealthComp->bEditableWhenInherited = true;

	MyGrappleController = CreateDefaultSubobject<UGrappleControlComponent>(TEXT("MyGrappleControlComponent"));
	MyGrappleController->bEditableWhenInherited = true;

	MyDashComp = CreateDefaultSubobject<UCharacterDashComponent>(TEXT("MyDashComponent"));
	MyDashComp->bEditableWhenInherited = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	MyMoveComp->MaxAcceleration = 2000;
	MyMoveComp->MaxWalkSpeed = 1000;
	MyMoveComp->AirControl = 0.5f;

	MyWeaponController->SetAttachSkel(SM_Arms, TEXT("Palm_R"));
	MyWeaponController->AddGun(StartWeapon, GunType::Pistol);

	MyHealthComp->SetMaxHealth(100);
	MyHealthComp->IHaveBeenHit.AddUniqueDynamic(this, &APlayerCharacter::TakenDamage);

	WallRunCap->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::BeginOverlap);
	WallRunCap->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::EndOverlap);

	if (ensure(HitMaterialParameter))
	{
		HitMaterialParameterinst = GetWorld()->GetParameterCollectionInstance(HitMaterialParameter);
	}

	StartRoll = GetControlRotation().Roll;
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (bWeWantToFire && MyWeaponController)
	{
		MyWeaponController->FireCurrentWeapon(MyCamera->GetComponentLocation(), MyCamera->GetComponentRotation());
	}

	WallRunning(DeltaSeconds);

	DamageEffectTimeDecrease();
}

void APlayerCharacter::WallRunning(float DeltaSeconds)
{
	if (bAmIWallRunning)
	{
		MyMoveComp->AddForce(WallRunDir * 50000);
	}
	else if (!bAmIWallRunning && CurrentWall && bJumpBeingHeld && MyMoveComp->IsFalling())
	{
		bAmIWallRunning = true;
		WallRunDir = FVector::CrossProduct(WallRayCast.Normal, GetActorUpVector());
		float WallDor = FVector::DotProduct(WallRunDir, GetActorForwardVector());
		if (WallDor < 0)
		{
			WallRunDir *= -1;
		}
		MyMoveComp->GravityScale = 0.2f;
		MyMoveComp->Velocity.Z = 0;
		float CamRollCheck = FVector::DotProduct(WallRayCast.Normal, GetActorRightVector());
		if (CamRollCheck >= 0)
		{
			TargetRoll = StartRoll + 20.0f;
		}
		else
		{
			TargetRoll = StartRoll - 20.0f;
		}
		JumpsUsed = 0;
	}

	FRotator CurrentRotation = GetController()->GetControlRotation();
	float CurrentRoll = CurrentRotation.Roll;
	float TargetRotationDiff = TargetRoll - CurrentRoll;
	if (TargetRotationDiff > 180)
	{
		TargetRotationDiff -= 360;
	}
	else if (TargetRotationDiff < -180)
	{
		TargetRotationDiff += 360;
	}
	float RollChange = (FMath::Clamp<float>(TargetRotationDiff, -1, +1)) * 60.0f * DeltaSeconds;
	CurrentRotation.Roll += RollChange;
	GetController()->SetControlRotation(CurrentRotation);
}

void APlayerCharacter::DamageEffectTimeDecrease()
{
	if (!bTakenDamageEffectOn) { return; }

	float CurrentEffect;
	bool GotValue = HitMaterialParameterinst->GetScalarParameterValue(TEXT("VignetteAmount"), CurrentEffect);

	if (GotValue)
	{
		if (CurrentEffect <= 0.0f)
		{
			HitMaterialParameterinst->SetScalarParameterValue(TEXT("VignetteAmount"), 0.0f);
			bTakenDamageEffectOn = false;
		}
		else
		{
			HitMaterialParameterinst->SetScalarParameterValue(TEXT("VignetteAmount"), CurrentEffect - (GetWorld()->DeltaTimeSeconds / 3));
		}
	}
}

void APlayerCharacter::MoveFoward(float Amount)
{
	if (Amount != 0 && !bAmIWallRunning)
	{
		AddMovementInput(GetActorForwardVector(), Amount);
	}
}

void APlayerCharacter::MoveRight(float Amount)
{
	if (Amount != 0 && !bAmIWallRunning)
	{
		AddMovementInput(GetActorRightVector(), Amount);
	}
}

void APlayerCharacter::Jump()
{
	if (JumpsUsed < 2)
	{
		JumpsUsed++;
		LaunchCharacter(JumpVel, false, true);
	}
	bJumpBeingHeld = true;
	EndWallRun();
}

void APlayerCharacter::JumpReleased()
{
	bJumpBeingHeld = false;
	EndWallRun();
}

void APlayerCharacter::SetFire()
{
	bWeWantToFire = !bWeWantToFire;

	if (!bWeWantToFire && MyWeaponController)
	{
		MyWeaponController->StopFire();
	}
}

void APlayerCharacter::FireGrapple()
{
	MyGrappleController->ShootGrappleGun(MyCamera->GetComponentLocation(), MyCamera->GetComponentRotation());
}

void APlayerCharacter::GrappleRelease()
{
	MyGrappleController->EndGrappleShoot();
}

void APlayerCharacter::Reload()
{
	MyWeaponController->Reload();
}

void APlayerCharacter::ChangeGunOne()
{
	MyWeaponController->ChangeGun(GunType::Pistol);
}

void APlayerCharacter::ChangeGunTwo()
{
	MyWeaponController->ChangeGun(GunType::AssultRifle);
}

void APlayerCharacter::ChangeGunThree()
{
	MyWeaponController->ChangeGun(GunType::RayGun);
}

void APlayerCharacter::TakenDamage()
{
	if (!ensure(HitMaterialParameterinst)) { return; }
	HitMaterialParameterinst->SetScalarParameterValue(TEXT("VignetteAmount"), 1.0f);
	bTakenDamageEffectOn = true;
}

void APlayerCharacter::Dash()
{
	MyDashComp->Dash();
}

void APlayerCharacter::EndWallRun()
{
	MyMoveComp->GravityScale = 1.0f;
	bAmIWallRunning = false;
	TargetRoll = StartRoll;
}

void APlayerCharacter::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->ActorHasTag("RunWall")) { return; }

	FHitResult HitOnWallRight;
	FHitResult HitOnWallLeft;
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(this);
	float WallDot = 0.0f;
	bool RightRayTest = GetWorld()->LineTraceSingleByChannel(HitOnWallRight, GetActorLocation(), GetActorLocation() + GetActorRightVector() * 1000, ECollisionChannel::ECC_Camera, TraceParams);
	bool LeftRayTest = GetWorld()->LineTraceSingleByChannel(HitOnWallLeft, GetActorLocation(), GetActorLocation() + -GetActorRightVector() * 1000, ECollisionChannel::ECC_Camera, TraceParams);

	if (RightRayTest && !LeftRayTest)
	{
		WallDot = FVector::DotProduct(HitOnWallRight.Normal, FVector::UpVector);
		WallRayCast = HitOnWallRight;
	}
	else if(!RightRayTest && LeftRayTest)
	{
		WallDot = FVector::DotProduct(HitOnWallLeft.Normal, FVector::UpVector);
		WallRayCast = HitOnWallLeft;
	}
	else if(RightRayTest && LeftRayTest)
	{
		if (FVector::Dist(GetActorLocation(), HitOnWallRight.ImpactPoint) < FVector::Dist(GetActorLocation(), HitOnWallLeft.ImpactPoint))
		{
			WallRayCast = HitOnWallRight;
		}
		else
		{
			WallRayCast = HitOnWallLeft;
		}
	}

	if (CurrentWall)
	{
		if (FVector::Dist(GetActorLocation(), OtherActor->GetActorLocation()) > FVector::Dist(GetActorLocation(), CurrentWall->GetActorLocation())) { return; }
		if (WallDot < -0.2f || WallDot > 0.2f) { return; }
	}
	else
	{
		if (WallDot < -0.2f || WallDot > 0.2f) { return; }
	}

	CurrentWall = OtherActor;
}

void APlayerCharacter::EndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor->ActorHasTag("RunWall")) { return; }

	if (OtherActor == CurrentWall)
	{
		CurrentWall = nullptr;
		EndWallRun();
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);
	//Look
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("TurnRight", this, &APawn::AddControllerYawInput);
	//Move
	PlayerInputComponent->BindAxis("Forward", this, &APlayerCharacter::MoveFoward);
	PlayerInputComponent->BindAxis("Right", this, &APlayerCharacter::MoveRight);
	//Jump
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Pressed, this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Jump", EInputEvent::IE_Released, this, &APlayerCharacter::JumpReleased);
	//Dash
	PlayerInputComponent->BindAction("Dash", EInputEvent::IE_Pressed, this, &APlayerCharacter::Dash);
	//Fire
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &APlayerCharacter::SetFire);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, this, &APlayerCharacter::SetFire);
	//GrappleShot
	PlayerInputComponent->BindAction("GrappleShot", EInputEvent::IE_Pressed, this, &APlayerCharacter::FireGrapple);
	PlayerInputComponent->BindAction("GrappleShot", EInputEvent::IE_Released, this, &APlayerCharacter::GrappleRelease);
	//Reload
	PlayerInputComponent->BindAction("Reload", EInputEvent::IE_Pressed, this, &APlayerCharacter::Reload);
	//Switch Weapon
	PlayerInputComponent->BindAction("Weapon1", EInputEvent::IE_Pressed, this, &APlayerCharacter::ChangeGunOne);
	PlayerInputComponent->BindAction("Weapon2", EInputEvent::IE_Pressed, this, &APlayerCharacter::ChangeGunTwo);
	PlayerInputComponent->BindAction("Weapon3", EInputEvent::IE_Pressed, this, &APlayerCharacter::ChangeGunThree);
}

void APlayerCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
	JumpsUsed = 0;
	EndWallRun();
}

