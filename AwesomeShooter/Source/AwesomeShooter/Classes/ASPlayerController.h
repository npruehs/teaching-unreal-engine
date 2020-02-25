#pragma once

#include "AwesomeShooter.h"
#include "GameFramework/PlayerController.h"
#include "ASPlayerController.generated.h"

UCLASS()
class AWESOMESHOOTER_API AASPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;

protected:
	/** Event when the player wants to see the scoreboard. */
	virtual void NotifyOnShowScoreboard();

	/** Event when the player no longer wants to see the scoreboard. */
	virtual void NotifyOnHideScoreboard();

	/** Event when the player wants to see the scoreboard. */
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnShowScoreboard"))
	void ReceiveOnShowScoreboard();

	/** Event when the player no longer wants to see the scoreboard. */
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "OnHideScoreboard"))
	void ReceiveOnHideScoreboard();

private:
	void InputMoveForward(float AxisValue);
	void InputStrafeRight(float AxisValue);
	void InputTurn(float AxisValue);
	void InputLookUp(float AxisValue);
	
	void InputJump();
    void InputFire();
	void InputRespawn();

	void InputShowScoreboard();
	void InputHideScoreboard();
};
