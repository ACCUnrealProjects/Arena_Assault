// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Actors/ZombieSpawnVolume.h"
#include "../Public/Enemy/Zombie.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AZombieSpawnVolume::AZombieSpawnVolume()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WhereToSpawn = CreateDefaultSubobject<UBoxComponent>(TEXT("Spawn Volume"));
	RootComponent = WhereToSpawn;

}

// Called when the game starts or when spawned
void AZombieSpawnVolume::BeginPlay()
{
	Super::BeginPlay();
	ZombieSpawnParams.Owner = this;

	if (isSpawning)
	{
		SpawnZombies();
	}

	ToSpawn = SpawnNumber;
}

// Called every frame
void AZombieSpawnVolume::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int i = 0; i < SpawnedEnemies.Num(); i++)
	{
		if (SpawnedEnemies[i] == nullptr || !SpawnedEnemies[i]->IsValidLowLevel())
		{
			UE_LOG(LogTemp, Warning, TEXT("Zombie Dead"));
			SpawnedEnemies.RemoveAt(i);
			i--;
		}
	}
}

UBoxComponent* AZombieSpawnVolume::GetWhereToSpawn() const
{
	return WhereToSpawn;
}

FVector AZombieSpawnVolume::GetRandomPointInVolume()
{
	return UKismetMathLibrary::RandomPointInBoundingBox(WhereToSpawn->Bounds.Origin, WhereToSpawn->Bounds.BoxExtent);
}

void AZombieSpawnVolume::SpawnZombies()
{
	if (!ZombiesToSpawn || ToSpawn <= 0) 
	{
		isSpawning = false;
		return; 
	}

	FVector SpawnLocation = GetRandomPointInVolume();
	FRotator ZombieRotation = FRotator(0, FMath::Rand() * 360.0f,0);

	AZombie* const NewZombie = GetWorld()->SpawnActor<AZombie>(ZombiesToSpawn, SpawnLocation, ZombieRotation, ZombieSpawnParams);
	SpawnedEnemies.Add(TWeakObjectPtr<AActor>(NewZombie));

	uint8 ZombieDrop = FMath::RandRange(0, 100);
	if (ZombieDrop <= DropChance)
	{
		int32 DropPicked = FMath::RandRange(0, Drops.Num()- 1);
		NewZombie->SetDrop(Drops[DropPicked]);
	}
	ToSpawn--;

	if (ToSpawn <= 0)
	{
		isSpawning = false;
	}
	else
	{
		GetWorld()->GetTimerManager().SetTimer(SpawnTimeHandler, this, &AZombieSpawnVolume::SpawnZombies, FMath::FRandRange(SpawnTimerLow, SpawnTimerHigh), false);
	}
}


bool AZombieSpawnVolume::HaveIFinishedSpawningAndAllDead()
{
	return isSpawning == false && SpawnedEnemies.Num() <= 0;
}