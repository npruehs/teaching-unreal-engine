#include "ASGameMode.h"

#include "GameFramework/Controller.h"
#include "GameFramework/PlayerState.h"

void AASGameMode::OnActorDestroyed(AActor* Actor, AController* InstigatedBy)
{
	// Increase score.
	if (!IsValid(InstigatedBy))
	{
		return;
	}

	APlayerState* PlayerState = InstigatedBy->GetPlayerState<APlayerState>();

	if (!IsValid(PlayerState))
	{
		return;
	}

	++PlayerState->Score;

	UE_LOG(LogAS, Log, TEXT("Increased score of %s (%s) to %f."), *PlayerState->GetName(),
		*PlayerState->GetPlayerName(), PlayerState->Score);

	// Check if game is over.
	CheckGameOver(InstigatedBy);
}

void AASGameMode::CheckGameOver(AController* Player)
{
	if (!IsValid(Player))
	{
		return;
	}

	APlayerState* PlayerState = Player->GetPlayerState<APlayerState>();

	if (!IsValid(PlayerState))
	{
		return;
	}

	if (PlayerState->Score >= ScoreLimit)
	{
		UE_LOG(LogAS, Log, TEXT("Score limit hit! Player %s (%s) won the match with a score of %f."), *PlayerState->GetName(),
			*PlayerState->GetPlayerName(), PlayerState->Score);
	}
}
