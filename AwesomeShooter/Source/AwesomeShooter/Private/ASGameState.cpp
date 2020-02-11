#include "ASGameState.h"

AASGameState::AASGameState()
{
	// Set reasonable default values.
	ScoreLimit = 10.0f;
}

float AASGameState::GetScoreLimit() const
{
	return ScoreLimit;
}
