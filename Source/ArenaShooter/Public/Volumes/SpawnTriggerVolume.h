// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerVolume.h"
#include "SpawnTriggerVolume.generated.h"

/**
 * 
 */
UCLASS()
class ARENASHOOTER_API ASpawnTriggerVolume : public ATriggerVolume
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnControl", meta = (AllowPrivateAccess = "true"))
	TArray <class AZombieSpawnVolume*> MySpawingVols;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "SpawnAction", meta = (AllowPrivateAccess = "true"))
	class AMovingPlatform* BlockingWall = nullptr;

	bool HaveIBeenTriggered = false;
	bool AmIActive = false;

protected:

	virtual void BeginPlay() override;

	UFUNCTION()
	void OnTriggerOverlap(AActor* OverlappedActor, AActor* OtherActor);

public:
	ASpawnTriggerVolume();

	virtual void Tick(float DeltaTime) override;
	
};
