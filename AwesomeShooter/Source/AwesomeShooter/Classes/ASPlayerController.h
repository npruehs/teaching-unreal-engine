#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ASPlayerController.generated.h"

UCLASS()
class AWESOMESHOOTER_API AASPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
	virtual void SetupInputComponent() override;

private:
	void InputMoveForward(float AxisValue);
	void InputStrafeRight(float AxisValue);

	/** Gets the current control rotation, ignoring pitch and roll. */
	inline FRotator GetYawRotation() const;
};
