#include "ASCollisionDamageComponent.h"

#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

UASCollisionDamageComponent::UASCollisionDamageComponent()
{
	// Set reasonable default values.
	Damage = 10.0f;
}

void UASCollisionDamageComponent::BeginPlay()
{
    Super::BeginPlay();

    // Early out if we don't have a valid owning actor.
    AActor* Owner = GetOwner();

    if (!IsValid(Owner))
    {
        return;
    }

    // Listen for overlap events of all primitive components of the actor.
	TArray<UPrimitiveComponent*> PrimitiveComponents;
    Owner->GetComponents(PrimitiveComponents);

    for (UPrimitiveComponent* PrimitiveComponent : PrimitiveComponents)
    {
        PrimitiveComponent->OnComponentBeginOverlap.AddDynamic(this, &UASCollisionDamageComponent::OnComponentBeginOverlap);
    }
}

void UASCollisionDamageComponent::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AActor* Owner = GetOwner();

	if (!IsValid(Owner))
	{
		return;
	}

	if (!IsValid(OtherActor))
	{
		return;
	}

	// Deal damage.
	AActor* DamageCauser = Owner;
	APawn* InstigatorPawn = IsValid(DamageCauser) ? DamageCauser->GetInstigator() : nullptr;
	AController* Instigator = IsValid(InstigatorPawn) ? InstigatorPawn->GetController() : nullptr;

	OtherActor->TakeDamage(Damage, FDamageEvent(), Instigator, DamageCauser);
	
	// Spawn effects.
	if (IsValid(ImpactEffect))
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Owner->GetActorLocation());
	}

	// Destroy projectile.
	Owner->Destroy();
}
