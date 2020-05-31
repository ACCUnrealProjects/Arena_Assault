// Alex Chatt Arena Shooter

#include "../Public/Component/HealthComponent.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* MyOwner = GetOwner();
	if (MyOwner)
	{
		MyOwner->OnTakeAnyDamage.AddUniqueDynamic(this, &UHealthComponent::TakeDamage);
	}
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHealthComponent::SetStartingHealth(uint16 StartHealth)
{
	StartingHealth = StartHealth;
	Health = StartHealth;
}

float UHealthComponent::GetHealthPercentage() const
{
	return (float)Health / (float)StartingHealth;
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	int intDamage = FPlatformMath::RoundToInt(Damage);
	intDamage = FMath::Clamp<int>(intDamage, 0, Health);
	Health -= intDamage;

	if (Health <= 0)
	{
		//I have died
	}
}

