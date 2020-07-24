// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Projectile/TracerRound.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

// Sets default values
ATracerRound::ATracerRound()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereCollider = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollider"));
	SphereCollider->SetVisibility(false);
	SphereCollider->SetNotifyRigidBodyCollision(true);
	SetRootComponent(SphereCollider);

	TraceMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TracerMesh"));
	TraceMesh->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	TraceMesh->SetRelativeLocation(FVector(0,0,0));
	TraceMesh->SetNotifyRigidBodyCollision(true);
	TraceMesh->CastShadow = false;
		
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->bAutoActivate = true;
	ProjectileMovement->InitialSpeed = 40000.0f;
	ProjectileMovement->Bounciness = 0.0f;
	ProjectileMovement->Friction = 0.0f;
	ProjectileMovement->InterpLocationTime = 0.0f;

}

// Called when the game starts or when spawned
void ATracerRound::BeginPlay()
{
	Super::BeginPlay();
	SphereCollider->OnComponentBeginOverlap.AddDynamic(this, &ATracerRound::TracerHit);
}


void ATracerRound::TracerHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Destroy();
}


