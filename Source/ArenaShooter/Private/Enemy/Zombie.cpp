// Fill out your copyright notice in the Description page of Project Settings.

#include "../Public/Enemy/Zombie.h"
#include "../Public/Component/HealthComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISense_sight.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AZombie::AZombie()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MyMoveComp = FindComponentByClass<UCharacterMovementComponent>();

	MyHealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("MyHealthComponent"));
	MyHealthComp->bEditableWhenInherited = true;

	ZombieMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ZombieMesh"));
	ZombieMesh->SetupAttachment(FindComponentByClass<USkeletalMeshComponent>());

	bUseControllerRotationYaw = false;
	MyMoveComp->bUseControllerDesiredRotation = true;
	MyMoveComp->bOrientRotationToMovement = true;

	SetUpMyStimulis();
}

void AZombie::SetUpMyStimulis()
{
	Stimulus = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("MyAIStim"));
	Stimulus->RegisterForSense(TSubclassOf<UAISense_Sight>());
	Stimulus->RegisterWithPerceptionSystem();
}

// Called when the game starts or when spawned
void AZombie::BeginPlay()
{
	Super::BeginPlay();

	MyHealthComp->SetMaxHealth(30);
}

// Called every frame
void AZombie::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AZombie::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AZombie::MeleeAttack(AActor* target)
{	
	if (!CanPunch || !target) { return; }

	UGameplayStatics::ApplyDamage(target, PunchDamage, GetController(), this, UDamageType::StaticClass());
	CanPunch = false;
	FTimerHandle PunchAttackTimer;
	GetWorld()->GetTimerManager().SetTimer(PunchAttackTimer, this, &AZombie::PunchCooldownComplete, PunchCoolDown, false);
}

void AZombie::PunchCooldownComplete()
{
	CanPunch = true;
}