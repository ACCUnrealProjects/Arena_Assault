// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterDashComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class ARENASHOOTER_API UCharacterDashComponent : public UActorComponent
{
	GENERATED_BODY()

public:	

private:
	// Dash check
	bool bCanDash = true;
	//Jump Dashes
	UPROPERTY(EditDefaultsOnly, Category = "Dashing", meta = (AllowPrivateAccess = "true"))
	float DashResetTime = 2.0f;
	UPROPERTY(EditDefaultsOnly, Category = "Dashing", meta = (AllowPrivateAccess = "true"))
	float DashDuration = 0.1f;
	UPROPERTY(EditDefaultsOnly, Category = "Dashing", meta = (AllowPrivateAccess = "true"))
	float DashingSpeed = 3000.0f;

	//Charactor move comp
	class UCharacterMovementComponent* MyMoveComp = nullptr;

	class ACharacter* MyCharacter = nullptr;

	//Dash Functions
	void DashEnd();
	void ResetDash();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Sets default values for this component's properties
	UCharacterDashComponent();

	void Dash();
};
