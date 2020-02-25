#include "ASSpawnSoundComponent.h"

#include "Kismet/GameplayStatics.h"

void UASSpawnSoundComponent::BeginPlay()
{
	Super::BeginPlay();

	AActor* Owner = GetOwner();

	if (!IsValid(Owner))
	{
		return;
	}

	if (!IsValid(SpawnSound))
	{
		UE_LOG(LogAS, Warning, TEXT("No spawn sound specified for %s."), *Owner->GetName());
		return;
	}

	UGameplayStatics::PlaySoundAtLocation(this, SpawnSound, Owner->GetActorLocation());
}
