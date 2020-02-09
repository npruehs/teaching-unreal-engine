#include "ASCharacter.h"

#include "Engine/World.h"

#include "ASWeaponComponent.h"

void AASCharacter::FireWeapon()
{
    // Early out if we haven't got an attached weapon.
    UASWeaponComponent* WeaponComponent = FindComponentByClass<UASWeaponComponent>();

    if (!IsValid(WeaponComponent))
    {
        return;
    }

    // Early out if the weapon doesn't have a projectile.
    TSubclassOf<AActor> ProjectileClass = WeaponComponent->GetProjectileClass();

    if (ProjectileClass == nullptr)
    {
        UE_LOG(LogAS, Warning, TEXT("Unable to fire, weapon component of %s has no projectile class set up."), *GetName());
        return;
    }

    // Spawn projectile in front of pawn.
    FVector ProjectileLocation = GetActorLocation() +
        GetActorForwardVector() * WeaponComponent->GetProjectileSpawnOffset();
    FRotator ProjectileRotation = GetActorRotation();

    // Store instigator for damage events.
    FActorSpawnParameters ActorSpawnParameters;
    ActorSpawnParameters.Instigator = this;

    AActor* Projectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, ProjectileLocation, ProjectileRotation,
        ActorSpawnParameters);
}
