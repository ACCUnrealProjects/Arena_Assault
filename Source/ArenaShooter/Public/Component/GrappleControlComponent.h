// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "GrappleControlComponent.generated.h"

class AGrappleGun;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARENASHOOTER_API UGrappleControlComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrappleControlComponent();

private:
	AGrappleGun* MyGrappleGun = nullptr;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GrappleGun")
	TSubclassOf<class AGrappleGun> GrappleGun = nullptr;

public:	

	void ShootGrappleGun(FRotator Dir);

	void EndGrappleShoot();
		
};
