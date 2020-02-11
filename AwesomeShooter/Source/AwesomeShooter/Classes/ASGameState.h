#pragma once

#include "AwesomeShooter.h"
#include "GameFramework/GameStateBase.h"
#include "ASGameState.generated.h"

UCLASS()
class AWESOMESHOOTER_API AASGameState : public AGameStateBase
{
    GENERATED_BODY()

public:
	AASGameState();

	/** Gets the score required for a player to win the match. */
	UFUNCTION(BlueprintPure)
	float GetScoreLimit() const;

private:
	/** Score required for a player to win the match. */
	UPROPERTY(EditDefaultsOnly)
	float ScoreLimit;
};
