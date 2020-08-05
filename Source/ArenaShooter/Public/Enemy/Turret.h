// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Turret.generated.h"

UCLASS()
class ARENASHOOTER_API ATurret : public APawn
{
	GENERATED_BODY()

private:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
	class UHealthComponent* MyHealthComp = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Aiming", meta = (AllowPrivateAccess = "true"))
	class UTurretAimingComponent* MyAimingComp = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UStaticMeshComponent* Body = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UTurretMesh* MyTurret = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Mesh", meta = (AllowPrivateAccess = "true"))
	class UBarrelMesh* MyBarrel = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	USoundBase* FireSound = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound", meta = (AllowPrivateAccess = "true"))
	USoundBase* ExplotionSound = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	class UParticleSystemComponent* TurretFireEffect = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* DeathExplotion = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Effects", meta = (AllowPrivateAccess = "true"))
	class UParticleSystem* HitEffect = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Firing", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ATracerRound> ProjectileBlueprint;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Fire", meta = (AllowPrivateAccess = "true"))
	float RecoilMinMax = 3.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Fire", meta = (AllowPrivateAccess = "true"))
	float FireRate = 0.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Fire", meta = (AllowPrivateAccess = "true"))
	float Damage = 5.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Fire", meta = (AllowPrivateAccess = "true"))
	float Range = 5000.0f;

	bool CanFire = true;

	void SetCanFireTrue();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Sets default values for this pawn's properties
	ATurret();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Fire(AActor* Target);

	void AimAt(AActor* Target);

	bool AmILookingAtTargetDir(FVector Direction);

	UFUNCTION()
	void Death();
};
