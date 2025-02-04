#include "ASAIController.h"

#include "BehaviorTree/BehaviorTree.h"

AASAIController::AASAIController()
{
	// We want player states for our AI, to allow them to score and win.
	bWantsPlayerState = true;
}

void AASAIController::OnPossess(APawn* InPawn)
{
    Super::OnPossess(InPawn);

    // Check behavior tree.
    if (!IsValid(BehaviorTree))
    {
        UE_LOG(LogAS, Error, TEXT("No behavior tree set up for %s."), *GetName());
        return;
    }

    // Create blackboard and run behavior tree.
    RunBehaviorTree(BehaviorTree);
}
