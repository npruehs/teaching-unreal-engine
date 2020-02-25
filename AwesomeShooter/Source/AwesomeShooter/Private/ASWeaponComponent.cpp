#include "ASWeaponComponent.h"

UASWeaponComponent::UASWeaponComponent()
{
	// Set reasonable default values.
	ProjectileSpawnOffset = 100.0f;
}

TSubclassOf<AActor> UASWeaponComponent::GetProjectileClass() const
{
    return ProjectileClass;
}

float UASWeaponComponent::GetProjectileSpawnOffset() const
{
    return ProjectileSpawnOffset;
}
