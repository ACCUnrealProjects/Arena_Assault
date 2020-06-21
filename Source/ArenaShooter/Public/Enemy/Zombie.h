// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Zombie.generated.h"

UCLASS()
class ARENASHOOTER_API AZombie : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AZombie();

private:

	class UCharacterMovementComponent* MyMoveComp = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HealthComponent")
	class UHealthComponent* MyHealthComp = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	class UStaticMeshComponent* ZombieMesh = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
