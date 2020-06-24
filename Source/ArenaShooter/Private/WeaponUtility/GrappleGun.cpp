// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/WeaponUtility/GrappleGun.h"
#include "../Public/WeaponUtility/GrabbleCable.h"
#include "GameFramework/Character.h"

// Sets default values
AGrappleGun::AGrappleGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GrappleShooter = CreateDefaultSubobject<USceneComponent>(TEXT("GrappleMesh"));
	SetRootComponent(GrappleShooter);

	GrappleCable = CreateDefaultSubobject<UGrabbleCable>(TEXT("GrappleHook"));
	GrappleCable->CableGravityScale = 0.0f;
	GrappleCable->CableWidth = 2.0f;
	GrappleCable->NumSides = 5;
	GrappleCable->CableLength = 0;
	GrappleCable->SolverIterations = 2;
	GrappleCable->NumSegments = 1;
	GrappleCable->SetupAttachment(GrappleShooter);
	GrappleCable->EndLocation = FVector(0);
	GrappleCable->ToggleVisibility(false);
}

// Called when the game starts or when spawned
void AGrappleGun::BeginPlay()
{
	Super::BeginPlay();

	if (!ensure(GrappleEndActorBP)) { return; }
	FActorSpawnParameters SpawnParams;
	GrappleEndActor = GetWorld()->SpawnActor<AActor>(GrappleEndActorBP, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), SpawnParams);
}

// Called every frame
void AGrappleGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ConnectionMade)
	{
		PullOwnerToEnd();
	}
	else if (ActiveGrapple)
	{
		GrappleConnect(DeltaTime);
	}

}

void AGrappleGun::PullOwnerToEnd()
{
	if (!OwnerCharacter) { return; }

	FVector PullDir = FVector(CableEndPoint - MyOwner->GetActorLocation()).GetSafeNormal();
	if (PullDir.Size() == 0) { return; }
	OwnerCharacter->LaunchCharacter(PullDir * GrapplePullForce, false, false);
}

void AGrappleGun::GrappleConnect(float DeltaTime)
{
	FVector GrappleActorPos = GrappleEndActor->GetActorLocation();

	if (FVector::Distance(GrappleActorPos, CableEndPoint) < 100.0f)
	{
		GrappleEndActor->SetActorLocation(CableEndPoint);
		ConnectionMade = true;
		return;
	}

	FVector InterpVect = FMath::VInterpTo(GrappleActorPos, CableEndPoint, DeltaTime, 30.0f);
	GrappleEndActor->SetActorLocation(InterpVect);
}

void AGrappleGun::SetMyOwner(AActor* GOwner)
{
	if (!GOwner) { return; }

	MyOwner = GOwner;
	OwnerCharacter = Cast<ACharacter>(MyOwner);
	GrappleShotParams.AddIgnoredActor(this);
	GrappleShotParams.AddIgnoredActor(MyOwner);
}

void AGrappleGun::GrappleAttempt(FVector GrappleStart, FRotator GrappleDir)
{
	FHitResult GrappleHot;
	FVector RayEnd = GrappleStart + (GrappleDir.Vector() * GrappleRange);

	if (GetWorld()->LineTraceSingleByChannel(GrappleHot, GrappleStart, RayEnd, ECollisionChannel::ECC_Camera, GrappleShotParams))
	{
		ActiveGrapple = true;
		CableEndPoint = GrappleHot.Location;
		GrappleEndActor->SetActorLocation(GrappleStart);
		FComponentReference ref;
		ref.OtherActor = GrappleEndActor;
		GrappleCable->AttachEndTo = ref;
		GrappleCable->ToggleVisibility(true);
	}
}

void AGrappleGun::DropGrapple()
{
	if (ActiveGrapple || ConnectionMade) { GrappleCable->ToggleVisibility(false); }
	ConnectionMade = false;
	ActiveGrapple = false;
	FComponentReference ref;
	ref.OtherActor = nullptr;
	GrappleCable->AttachEndTo = ref;
}

