#pragma once

#include "AwesomeShooter.h"
#include "Components/ActorComponent.h"
#include "ASHealthComponent.generated.h"

class AActor;
class AController;
class UDamageType;

/** Adds a health value to the actor, destroying it when depleted. */
UCLASS(meta = (BlueprintSpawnableComponent))
class AWESOMESHOOTER_API UASHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UASHealthComponent();

	virtual void BeginPlay() override;

	/** Gets how much damage the actor can still sustain before being destroyed. */
	UFUNCTION(BlueprintPure)
	float GetCurrentHealth() const;

    /** Gets how much damage the actor can still sustain before being destroyed, as value between 0 and 1. */
    UFUNCTION(BlueprintPure)
    float GetCurrentHealthRatio() const;

private:
	/** How much damage the actor can still sustain before being destroyed. */
	UPROPERTY()
	float CurrentHealth;

	/** How much damage the actor can sustain before being destroyed. */
	UPROPERTY(EditDefaultsOnly)
	float MaximumHealth;

	UFUNCTION()
	void OnTakeAnyDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy,
		AActor* DamageCauser);
};
