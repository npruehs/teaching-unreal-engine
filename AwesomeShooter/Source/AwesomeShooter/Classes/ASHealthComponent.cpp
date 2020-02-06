#include "ASHealthComponent.h"

#include "ASGameMode.h"

UASHealthComponent::UASHealthComponent()
{
	// Set reasonable default values.
	MaximumHealth = 100.0f;
}

void UASHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// Listen for damage events.
	AActor* Owner = GetOwner();

	if (!IsValid(Owner))
	{
		return;
	}

	Owner->OnTakeAnyDamage.AddDynamic(this, &UASHealthComponent::OnTakeAnyDamage);

	// Set initial health.
	CurrentHealth = MaximumHealth;
}

float UASHealthComponent::GetCurrentHealth() const
{
	return CurrentHealth;
}

void UASHealthComponent::OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType,
	AController* InstigatedBy, AActor* DamageCauser)
{
	// Check if we're already dead.
	AActor* Owner = GetOwner();

	if (!IsValid(Owner))
	{
		return;
	}

	if (CurrentHealth <= 0.0f)
	{
		return;
	}

	// Reduce health.
	CurrentHealth -= Damage;

	UE_LOG(LogAS, Log, TEXT("%s has taken %f damage, reducing health to %f."), *Owner->GetName(), Damage, CurrentHealth);

	// Check if we're dead now.
	if (CurrentHealth <= 0.0f)
	{
		// Destroy actor.
		Owner->Destroy();

		UE_LOG(LogAS, Log, TEXT("%s has been killed by %s (instigated by %s)!"), *Owner->GetName(),
			IsValid(DamageCauser) ? *DamageCauser->GetName() : TEXT("nullptr"),
			IsValid(InstigatedBy) ? *InstigatedBy->GetName() : TEXT("nullptr"));

		// Notify game mode.
		AASGameMode* GameMode = GetWorld()->GetAuthGameMode<AASGameMode>();

		if (IsValid(GameMode))
		{
			GameMode->OnActorDestroyed(Owner, InstigatedBy);
		}
	}
}
