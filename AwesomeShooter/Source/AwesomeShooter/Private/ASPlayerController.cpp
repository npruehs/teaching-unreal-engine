#include "ASPlayerController.h"

#include "GameFramework/Character.h"

#include "ASCharacter.h"

void AASPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (!IsValid(InputComponent))
	{
		return;
	}

	InputComponent->BindAxis(TEXT("MoveForward"), this, &AASPlayerController::InputMoveForward);
	InputComponent->BindAxis(TEXT("StrafeRight"), this, &AASPlayerController::InputStrafeRight);
	InputComponent->BindAxis(TEXT("Turn"), this, &AASPlayerController::InputTurn);
	InputComponent->BindAxis(TEXT("LookUp"), this, &AASPlayerController::InputLookUp);

	InputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &AASPlayerController::InputJump);
    InputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &AASPlayerController::InputFire);
	InputComponent->BindAction(TEXT("Respawn"), IE_Pressed, this, &AASPlayerController::InputRespawn);

	InputComponent->BindAction(TEXT("ShowScoreboard"), IE_Pressed, this, &AASPlayerController::InputShowScoreboard);
	InputComponent->BindAction(TEXT("ShowScoreboard"), IE_Released, this, &AASPlayerController::InputHideScoreboard);
}

void AASPlayerController::NotifyOnShowScoreboard()
{
	ReceiveOnShowScoreboard();
}

void AASPlayerController::NotifyOnHideScoreboard()
{
	ReceiveOnHideScoreboard();
}

void AASPlayerController::InputMoveForward(float AxisValue)
{
	// Early out if we haven't got a valid pawn.
	if (!IsValid(GetPawn()))
	{
		return;
	}

	// Scale movement by input axis value.
	FVector Forward = GetPawn()->GetActorForwardVector();

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

	// Scale movement by input axis value.
	FVector Right = GetPawn()->GetActorRightVector();

	// Apply input.
	GetPawn()->AddMovementInput(Right, AxisValue);
}

void AASPlayerController::InputTurn(float AxisValue)
{
	AddYawInput(AxisValue);
}

void AASPlayerController::InputLookUp(float AxisValue)
{
	AddPitchInput(AxisValue);
}

void AASPlayerController::InputJump()
{
	if (!IsValid(GetCharacter()))
	{
		return;
	}

	// Perform jump.
	GetCharacter()->Jump();
}

void AASPlayerController::InputFire()
{
    // Early out if we haven't got a valid character.
    AASCharacter* ASCharacter = Cast<AASCharacter>(GetCharacter());

    if (!IsValid(ASCharacter))
    {
        return;
    }

    ASCharacter->FireWeapon();
}

void AASPlayerController::InputRespawn()
{
	// Early out if we HAVE got a valid pawn.
	if (IsValid(GetPawn()))
	{
		return;
	}

	// Tell server we want to respawn.
	ServerRestartPlayer();
}

void AASPlayerController::InputShowScoreboard()
{
	NotifyOnShowScoreboard();
}

void AASPlayerController::InputHideScoreboard()
{
	NotifyOnHideScoreboard();
}
