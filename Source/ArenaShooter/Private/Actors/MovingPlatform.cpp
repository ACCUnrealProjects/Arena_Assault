// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Actors/MovingPlatform.h"

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
	
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AmIActive)
	{
		if (AmIMovingToPoint)
		{
			MoveToPoint();
		}
		else
		{
			MoveBack();
		}
	}

}

void AMovingPlatform::MoveToPoint()
{

}

void AMovingPlatform::MoveBack()
{

}


void AMovingPlatform::ActivateMove()
{
	AmIActive = true;
	AmIMovingToPoint = !AmIMovingToPoint;
}
