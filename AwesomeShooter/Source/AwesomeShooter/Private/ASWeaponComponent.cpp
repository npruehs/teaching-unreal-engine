#include "ASWeaponComponent.h"

TSubclassOf<AActor> UASWeaponComponent::GetProjectileClass() const
{
    return ProjectileClass;
}

float UASWeaponComponent::GetProjectileSpawnOffset() const
{
    return ProjectileSpawnOffset;
}
