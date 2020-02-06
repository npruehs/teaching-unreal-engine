#include "ASPlayerController.h"

#include "Engine/World.h"
#include "GameFramework/Character.h"

#include "ASWeaponComponent.h"

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
    // Early out if we haven't got a valid pawn.
    if (!IsValid(GetPawn()))
    {
        return;
    }

    // Early out if we haven't got an attached weapon.
    UASWeaponComponent* WeaponComponent = GetPawn()->FindComponentByClass<UASWeaponComponent>();

    if (!IsValid(WeaponComponent))
    {
        return;
    }

    // Early out if the weapon doesn't have a projectile.
    TSubclassOf<AActor> ProjectileClass = WeaponComponent->GetProjectileClass();

    if (ProjectileClass == nullptr)
    {
        UE_LOG(LogAS, Warning, TEXT("Unable to fire, weapon component of %s has no projectile class set up."), *GetPawn()->GetName());
        return;
    }

    // Spawn projectile in front of pawn.
    FVector ProjectileLocation = GetPawn()->GetActorLocation() +
        GetPawn()->GetActorForwardVector() * WeaponComponent->GetProjectileSpawnOffset();
    FRotator ProjectileRotation = GetPawn()->GetActorRotation();

	// Store instigator for damage events.
	FActorSpawnParameters ActorSpawnParameters;
	ActorSpawnParameters.Instigator = GetPawn();

    AActor* Projectile = GetWorld()->SpawnActor<AActor>(ProjectileClass, ProjectileLocation, ProjectileRotation,
		ActorSpawnParameters);
}
