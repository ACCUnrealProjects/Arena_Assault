// Fill out your copyright notice in the Description page of Project Settings.


#include "../Public/Actors/Target.h"
#include "../Public/Component/HealthComponent.h"

// Sets default values
ATarget::ATarget()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	MyHealthComp = CreateDefaultSubobject<UHealthComponent>(TEXT("MyHealthComponent"));
	MyHealthComp->bEditableWhenInherited = true;

}

// Called when the game starts or when spawned
void ATarget::BeginPlay()
{
	Super::BeginPlay();

	MyHealthComp->SetMaxHealth(1);
	MyHealthComp->IHaveDied.AddUniqueDynamic(this, &ATarget::OnDeath);
}

// Called every frame
void ATarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATarget::OnDeath()
{
	Destroy();
}

