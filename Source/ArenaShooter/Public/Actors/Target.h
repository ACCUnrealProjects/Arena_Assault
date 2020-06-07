// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Target.generated.h"

UCLASS()
class ARENASHOOTER_API ATarget : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATarget();

private:

	UFUNCTION()
	void OnDeath();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Setup")
	class UStaticMeshComponent* TargetMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "HealthComponent")
	class UHealthComponent* MyHealthComp = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


};
