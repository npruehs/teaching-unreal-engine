#pragma once

#include "AwesomeShooter.h"
#include "Components/ActorComponent.h"
#include "ASSpawnSoundComponent.generated.h"

/** Plays a sound when the actor spawns. */
UCLASS(meta = (BlueprintSpawnableComponent))
class AWESOMESHOOTER_API UASSpawnSoundComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	virtual void BeginPlay() override;

private:
	/** Sound to play when the actor spawns. */
	UPROPERTY(EditDefaultsOnly)
	USoundBase* SpawnSound;
};
