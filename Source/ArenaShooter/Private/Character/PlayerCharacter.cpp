// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Character/PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "../Public/Component/WeaponControllerComponet.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Public/Weapons/Base_Weapon.h"
#include "Components/CapsuleComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCapsuleSize(55.f, 90.0f);

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
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	MyMoveComp->MaxAcceleration = 4000;
	MyMoveComp->MaxWalkSpeed = 600;
	MyMoveComp->AirControl = 0.5f;

	MyWeaponController = FindComponentByClass<UWeaponControllerComponet>();
	MyWeaponController->SetAttachSkel(SM_Arms, TEXT("Palm_R"));
	FActorSpawnParameters SpawnParams;
	MyWeaponController->AddGun(StartWeapon);
}

void APlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (WeWantToFire && MyWeaponController)
	{
		MyWeaponController->FireCurrentWeapon(MyCamera->GetComponentLocation(), MyCamera->GetComponentRotation());
	}
}

void APlayerCharacter::MoveFoward(float Amount)
{
	if (Amount != 0)
	{
		AddMovementInput(GetActorForwardVector(), Amount);
	}
}

void APlayerCharacter::MoveRight(float Amount)
{
	if (Amount != 0)
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
}

void APlayerCharacter::SetFire()
{
	WeWantToFire = !WeWantToFire;

	if (!WeWantToFire && MyWeaponController)
	{
		MyWeaponController->StopFire();
	}
}

void APlayerCharacter::Reload()
{
	if (!MyWeaponController) { return; }
	MyWeaponController->Reload();
}

void APlayerCharacter::ChangeGunOne()
{
	if (!MyWeaponController) { return; }
	MyWeaponController->ChangeGun(1);
}

void APlayerCharacter::ChangeGunTwo()
{
	if (!MyWeaponController) { return; }
	MyWeaponController->ChangeGun(2);
}

void APlayerCharacter::ChangeGunThree()
{
	if (!MyWeaponController) { return; }
	MyWeaponController->ChangeGun(3);
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
	//Fire
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &APlayerCharacter::SetFire);
	PlayerInputComponent->BindAction("Fire", EInputEvent::IE_Released, this, &APlayerCharacter::SetFire);
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
}

