#include "ASPlayerController.h"

#include "Kismet/KismetMathLibrary.h"

void AASPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (!IsValid(InputComponent))
	{
		return;
	}

	InputComponent->BindAxis(TEXT("MoveForward"), this, &AASPlayerController::InputMoveForward);
	InputComponent->BindAxis(TEXT("StrafeRight"), this, &AASPlayerController::InputStrafeRight);
}

void AASPlayerController::InputMoveForward(float AxisValue)
{
	// Early out if we haven't got a valid pawn.
	if (!IsValid(GetPawn()))
	{
		return;
	}

	// We're interested in character yaw, only, for WSAD movement.
	// Otherwise, we'd probable start flying pretty soon.
	FRotator YawRotation = GetYawRotation();

	// Scale movement by input axis value.
	FVector Forward = UKismetMathLibrary::GetForwardVector(YawRotation);

	// Apply input.
	GetPawn()->AddMovementInput(Forward, AxisValue);
}

void AASPlayerController::InputStrafeRight(float AxisValue)
{
	// Early out if we haven't got a valid pawn.
	if (!IsValid(GetPawn()))
	{
		return;
	}

	// We're interested in character yaw, only, for WSAD movement.
	// Otherwise, we'd probable start flying pretty soon.
	FRotator YawRotation = GetYawRotation();

	// Scale movement by input axis value.
	FVector Right = UKismetMathLibrary::GetRightVector(YawRotation);

	// Apply input.
	GetPawn()->AddMovementInput(Right, AxisValue);
}

FRotator AASPlayerController::GetYawRotation() const
{
	return FRotator(0, 0, GetControlRotation().Yaw);
}
