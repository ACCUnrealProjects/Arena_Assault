// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/PickUps/PickUps.h"
#include "Components/CapsuleComponent.h"

APickUps::APickUps()
{
	PickUpMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PickupMesh"));
	SetRootComponent(PickUpMesh);
	PickUpCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionCapsule"));
	PickUpCollider->SetupAttachment(PickUpMesh);
	PickUpCollider->SetGenerateOverlapEvents(true);
	PickUpCollider->OnComponentBeginOverlap.AddDynamic(this, &APickUps::BeginOverlap);
}

void APickUps::BeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if(TriggerPickUp(OtherActor))
	{
		Destroy();
	}
}