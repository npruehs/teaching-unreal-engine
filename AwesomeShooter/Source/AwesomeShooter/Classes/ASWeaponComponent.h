#pragma once

#include "AwesomeShooter.h"
#include "Components/ActorComponent.h"
#include "GameFramework/Actor.h"
#include "ASWeaponComponent.generated.h"

/** Adds a weapon to the actor, that fires projetiles. */
UCLASS(meta = (BlueprintSpawnableComponent))
class AWESOMESHOOTER_API UASWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    /** Gets the class of the projectile to fire. */
    TSubclassOf<AActor> GetProjectileClass() const;

    /** Gets how much to spawn the projectile in front of the weapon, in cm. */
    float GetProjectileSpawnOffset() const;

private:
    /** Class of the projectile to fire. */
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<AActor> ProjectileClass;

    /** How much to spawn the projectile in front of the weapon, in cm. */
    UPROPERTY(EditDefaultsOnly)
    float ProjectileSpawnOffset;
};
