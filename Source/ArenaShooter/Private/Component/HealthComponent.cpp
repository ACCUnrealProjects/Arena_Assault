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

void UHealthComponent::SetMaxHealth(int32 StartHealth)
{
	MaxHealth = StartHealth;
	Health = StartHealth;
}

void UHealthComponent::IncreaseHealth(int32 HealthIncrease)
{
	Health = FMath::Min(Health + HealthIncrease, MaxHealth);
}

float UHealthComponent::GetHealthPercentage() const
{
	return (float)Health / (float)MaxHealth;
}

void UHealthComponent::TakeDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	int intDamage = FPlatformMath::RoundToInt(Damage);
	intDamage = FMath::Clamp<int>(intDamage, 0, Health);
	Health -= intDamage;

	if (Health <= 0)
	{
		IHaveDied.Broadcast();
	}
	else if (Damage > 0)
	{
		IHaveBeenHit.Broadcast();
	}
}

