// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Component/CharacterDashComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Character.h"

UCharacterDashComponent::UCharacterDashComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UCharacterDashComponent::BeginPlay()
{
	Super::BeginPlay();

	MyMoveComp = GetOwner()->FindComponentByClass<UCharacterMovementComponent>();
	MyCharacter = Cast<ACharacter>(GetOwner());
	if (!MyCharacter)
	{
		UE_LOG(LogTemp, Warning, TEXT("Character cast not working"));
	}
}

void UCharacterDashComponent::Dash()
{
	if (!bCanDash || !MyCharacter || !MyMoveComp) { return; }
	bCanDash = false;
	MyMoveComp->BrakingFrictionFactor = 0.0f;
	FVector VelDir = MyMoveComp->Velocity.GetSafeNormal();
	VelDir.Z = 0;
	if (VelDir.IsZero()) { VelDir = MyCharacter->GetActorForwardVector(); }
	MyCharacter->LaunchCharacter(VelDir * DashingSpeed, false, false);
	FTimerHandle DashResetTimer;
	GetWorld()->GetTimerManager().SetTimer(DashResetTimer, this, &UCharacterDashComponent::ResetDash, DashResetTime, false);
	FTimerHandle DashTimer;
	GetWorld()->GetTimerManager().SetTimer(DashTimer, this, &UCharacterDashComponent::DashEnd, DashDuration, false);
}


void UCharacterDashComponent::DashEnd()
{
	MyMoveComp->BrakingFrictionFactor = 1.0f;
	//MyMoveComp->StopMovementImmediately();
}

void UCharacterDashComponent::ResetDash()
{
	bCanDash = true;
}

