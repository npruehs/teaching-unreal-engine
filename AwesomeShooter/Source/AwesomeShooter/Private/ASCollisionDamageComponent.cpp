#include "ASCollisionDamageComponent.h"

#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"

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
    TArray<UActorComponent*> ActorComponents = Owner->GetComponentsByClass(UPrimitiveComponent::StaticClass());

    for (UActorComponent* ActorComponent : ActorComponents)
    {
        UPrimitiveComponent* PrimitiveComponent = Cast<UPrimitiveComponent>(ActorComponent);
        PrimitiveComponent->OnComponentBeginOverlap.AddDynamic(this, &UASCollisionDamageComponent::OnComponentBeginOverlap);
    }
}

void UASCollisionDamageComponent::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValid(GetOwner()) || !IsValid(OtherActor))
	{
		return;
	}

	// Deal damage.
	AActor* DamageCauser = GetOwner();
	APawn* InstigatorPawn = IsValid(DamageCauser) ? DamageCauser->GetInstigator() : nullptr;
	AController* Instigator = IsValid(InstigatorPawn) ? InstigatorPawn->GetController() : nullptr;

	OtherActor->TakeDamage(Damage, FDamageEvent(), Instigator, DamageCauser);
	
	// Destroy projectile.
	GetOwner()->Destroy();
}
