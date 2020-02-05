#pragma once

#include "AwesomeShooter.h"
#include "Components/ActorComponent.h"
#include "ASCollisionDamageComponent.generated.h"

class AActor;
class UPrimitiveComponent;

/** Deals damage to any actor colliding with the actor. */
UCLASS(meta = (BlueprintSpawnableComponent))
class AWESOMESHOOTER_API UASCollisionDamageComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    virtual void BeginPlay() override;

private:
    UFUNCTION()
    void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
