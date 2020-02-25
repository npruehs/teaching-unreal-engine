#pragma once

#include "AwesomeShooter.h"
#include "GameFramework/Character.h"
#include "ASCharacter.generated.h"

UCLASS()
class AWESOMESHOOTER_API AASCharacter : public ACharacter
{
    GENERATED_BODY()

public:
    /** Fires the current weapon of this character, in forward direction. */
    UFUNCTION(BlueprintCallable)
    void FireWeapon();
};
