#pragma once

#include "AwesomeShooter.h"
#include "GameFramework/GameModeBase.h"
#include "ASAIController.h"
#include "ASGameMode.generated.h"

class AActor;
class AController;

UCLASS()
class AWESOMESHOOTER_API AASGameMode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AASGameMode();

    virtual void StartPlay() override;

	/** Notifies this game mode that the specified actor has been destroyed by the passed instigator. */
	void OnActorDestroyed(AActor* Actor, AController* Instigator);

private:
	/** Score required for a player to win the match. */
	UPROPERTY(EditDefaultsOnly)
	float ScoreLimit;

    /** AI controller to have players fight against. */
    UPROPERTY(EditDefaultsOnly)
    TSubclassOf<AASAIController> AIControllerClass;

    /** Spawns and starts a single AI player. */
    void SpawnAIPlayer();

	/** Checks whether the match is over and the specified player has won. */
	void CheckGameOver(AController* Player);
};
