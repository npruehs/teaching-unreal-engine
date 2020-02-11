#pragma once

#include "AwesomeShooter.h"
#include "AIController.h"
#include "ASAIController.generated.h"

class UBehaviorTree;

UCLASS()
class AWESOMESHOOTER_API AASAIController : public AAIController
{
    GENERATED_BODY()

public:
	AASAIController();

    virtual void OnPossess(APawn* InPawn) override;

private:
    /** Behavior tree to use for this AI. */
    UPROPERTY(EditDefaultsOnly)
    UBehaviorTree* BehaviorTree;
};
