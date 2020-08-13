// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Volumes/SpawnTriggerVolume.h"
#include "../Public/Actors/ZombieSpawnVolume.h"
#include "../Public/Actors/MovingPlatform.h"

ASpawnTriggerVolume::ASpawnTriggerVolume()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ASpawnTriggerVolume::BeginPlay()
{
	Super::BeginPlay();

	OnActorBeginOverlap.AddDynamic(this, &ASpawnTriggerVolume::OnTriggerOverlap);
	HaveIBeenTriggered = false;
}

void ASpawnTriggerVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (AmIActive)
	{
		for (int i = 0; i < MySpawingVols.Num(); i++)
		{
			if (MySpawingVols[i]->HaveIFinishedSpawningAndAllDead())
			{
				AZombieSpawnVolume* ToDestory = MySpawingVols[i];
				MySpawingVols.RemoveAt(i);
				i--;
				ToDestory->Destroy();
			}
		}

		if (MySpawingVols.Num() <= 0)
		{
			AmIActive = false;

			for (auto Wall : BlockingWall)
			{
				Wall->ActivateMove();
			}
		}
	}
}

void ASpawnTriggerVolume::OnTriggerOverlap(AActor* OverlappedActor, AActor* OtherActor)
{
	if (HaveIBeenTriggered) { return; }

	if (OtherActor == GetWorld()->GetFirstPlayerController()->GetPawn())
	{
		for (auto Wall : BlockingWall)
		{
			Wall->ActivateMove();
		}

		for (auto SpawnVol : MySpawingVols)
		{
			SpawnVol->SpawnZombies();
		}

		HaveIBeenTriggered = true;
		AmIActive = true;
	}

}