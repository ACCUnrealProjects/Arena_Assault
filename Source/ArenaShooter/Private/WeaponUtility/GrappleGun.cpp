// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/WeaponUtility/GrappleGun.h"
#include "../Public/WeaponUtility/GrabbleCable.h"
#include "DrawDebugHelpers.h"

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
	GrappleCable->ToggleVisibility(false);
	GrappleCable->SetupAttachment(GrappleShooter);

}

// Called when the game starts or when spawned
void AGrappleGun::BeginPlay()
{
	Super::BeginPlay();
	GrappleCable->EndLocation = FVector(0);
}

// Called every frame
void AGrappleGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ConnectionMade)
	{
		PullOwnerToEnd();
	}

}

void AGrappleGun::PullOwnerToEnd()
{

}

void AGrappleGun::SetMyOwner(AActor* GOwner)
{
	if (!GOwner) { return; }

	MyOwner = GOwner;
}

void AGrappleGun::GrappleAttempt(FRotator Dir)
{
	GrappleCable->ToggleVisibility(true);
	GrappleCable->SetWorldRotation(Dir);

	FHitResult GrappleHot;
	FVector RayEnd = GetActorLocation() + (Dir.Vector() * GrappleRange);

	FCollisionQueryParams GrappleShotParams;
	GrappleShotParams.AddIgnoredActor(this);
	GrappleShotParams.AddIgnoredActor(MyOwner);

	if (GetWorld()->LineTraceSingleByChannel(GrappleHot, GetActorLocation(), RayEnd, ECollisionChannel::ECC_Camera, GrappleShotParams))
	{
		ActiveGrapple = true;
		CableEndPoint = GrappleHot.Location;
		GrappleCable->SetWorldLocation(GrappleHot.Location);
		DrawDebugLine(GetWorld(), GetActorLocation(), GrappleHot.Location, FColor(0, 255, 0), true, 0, 0, 10);
	}
}

void AGrappleGun::DropGrapple()
{
	GrappleCable->ToggleVisibility(false);
	ConnectionMade = false;
	ActiveGrapple = false;
}

