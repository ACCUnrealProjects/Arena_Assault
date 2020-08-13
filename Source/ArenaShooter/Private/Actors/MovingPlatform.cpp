// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Actors/MovingPlatform.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(MyMesh);
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	StartPos = GetActorLocation();
	AmIMovingToPoint = AmIActive;
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AmIActive)
	{
		if (AmIMovingToPoint)
		{
			MoveToPoint(DeltaTime);
		}
		else
		{
			MoveBack(DeltaTime);
		}
	}

}

void AMovingPlatform::MoveToPoint(float DeltaTime)
{
	FVector Direction = (MovePoint - GetActorLocation()).GetSafeNormal();
	//FVector NewLocation = UKismetMathLibrary::VInterpTo(GetActorLocation(), MovePoint, DeltaTime, MoveSpeed);
	FVector Velocity = (Direction * MoveSpeed * DeltaTime);
	SetActorLocation(GetActorLocation() + Velocity);

	if (GetActorLocation().Equals(MovePoint, 5.0f))
	{
		if (!LoopMove)
		{
			AmIActive = false;
		}
		else
		{
			AmIMovingToPoint = false;
		}
	}
}

void AMovingPlatform::MoveBack(float DeltaTime)
{
	FVector Direction = (StartPos - GetActorLocation()).GetSafeNormal();
	//FVector NewLocation = UKismetMathLibrary::VInterpTo(GetActorLocation(), StartPos, DeltaTime, MoveSpeed);
	FVector Velocity = (Direction * MoveSpeed * DeltaTime);
	SetActorLocation(GetActorLocation() + Velocity);

	if (GetActorLocation().Equals(StartPos, 5.0f))
	{
		if (!LoopMove)
		{
			AmIActive = false;
		}
		else
		{
			AmIMovingToPoint = true;
		}
	}
}


void AMovingPlatform::ActivateMove()
{
	AmIActive = true;
	AmIMovingToPoint = !AmIMovingToPoint;
}
