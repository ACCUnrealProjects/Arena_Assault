// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Component/GrappleControlComponent.h"
#include "../Public/WeaponUtility/GrappleGun.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
UGrappleControlComponent::UGrappleControlComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

}

void UGrappleControlComponent::BeginPlay()
{
	Super::BeginPlay();

	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = Cast<APawn>(GetOwner());

	if (!ensure(GrappleGun)) { return; }
	MyGrappleGun = GetWorld()->SpawnActor<AGrappleGun>(GrappleGun, GetOwner()->GetActorLocation(), GetOwner()->GetActorRotation(), SpawnParams);
	MyGrappleGun->SetMyOwner(GetOwner());
	MyGrappleGun->AttachToActor(GetOwner(), FAttachmentTransformRules::KeepWorldTransform);
}

void UGrappleControlComponent::ShootGrappleGun(FVector GrappleStartPos, FRotator GrappleDir)
{
	if (!ensure(MyGrappleGun)) { return; }
	MyGrappleGun->GrappleAttempt(GrappleStartPos, GrappleDir);
}

void UGrappleControlComponent::EndGrappleShoot()
{
	if (!ensure(MyGrappleGun)) { return; }
	MyGrappleGun->DropGrapple();

}