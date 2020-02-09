#include "ASGameMode.h"

#include "Engine/World.h"

#include "GameFramework/Controller.h"
#include "GameFramework/PlayerState.h"

AASGameMode::AASGameMode()
{
	// Set reasonable default values.
	ScoreLimit = 10.0f;
}

void AASGameMode::StartPlay()
{
    Super::StartPlay();

    // Spawn single AI player for now.
    SpawnAIPlayer();
}

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

void AASGameMode::SpawnAIPlayer()
{
    // Check AI controller class.
    if (AIControllerClass == nullptr)
    {
        UE_LOG(LogAS, Error, TEXT("Failed to spawn AI player: No AIControllerClass set for %s."), *GetName());
        return;
    }

    // Spawn AI.
    FActorSpawnParameters SpawnInfo;
    SpawnInfo.Instigator = Instigator;
    SpawnInfo.ObjectFlags |= RF_Transient; // We never want to save player controllers into a map

    AASAIController* NewAI = GetWorld()->SpawnActor<AASAIController>(
        AIControllerClass, FVector::ZeroVector, FRotator::ZeroRotator, SpawnInfo);

    if (!IsValid(NewAI))
    {
        UE_LOG(LogAS, Error, TEXT("Failed to spawn AI %s."), *AIControllerClass->GetName());
        return;
    }

    // Start AI (find player start, spawn pawn, etc.)
    RestartPlayer(NewAI);
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
