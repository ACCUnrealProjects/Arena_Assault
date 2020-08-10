// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Volumes/SpawnTriggerVolume.h"
#include "../Public/Actors/MovingPlatform.h"

ASpawnTriggerVolume::ASpawnTriggerVolume()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASpawnTriggerVolume::BeginPlay()
{
	OnActorBeginOverlap.AddDynamic(this, &ASpawnTriggerVolume::OnTriggerOverlap);
	HaveIBeenTriggered = false;
}

void ASpawnTriggerVolume::Tick(float DeltaTime)
{
	if (AmIActive)
	{

	}
}

void ASpawnTriggerVolume::OnTriggerOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (HaveIBeenTriggered) { return; }

	if (OverlappedActor == GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		if (BlockingWall)
		{

		}

		for (auto SpawnVol : MySpawingVols)
		{

		}

		HaveIBeenTriggered = true;
		AmIActive = true;
	}

}