// Fill out your copyright notice in the Description page of Project Settings.


#include "TankController.h"
#include "TankPawn.h"

void ATankController::SetupInputComponent()
{
	Super::SetupInputComponent();

	InputComponent->BindAxis("MoveForward", this, &ATankController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ATankController::MoveRight);
	InputComponent->BindAxis("RotateRight", this, &ATankController::RotateRight);
}


void ATankController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector mouseDirection;
	DeprojectMousePositionToWorld(MousePos, mouseDirection);
	FVector TankPosition = TankPawn->GetActorLocation();
	MousePos.Z = TankPosition.Z;
	FVector dir = MousePos - TankPosition;
	dir.Normalize();
	MousePos = TankPosition + dir * 1000.0f;
	DrawDebugLine(GetWorld(), TankPosition, MousePos, FColor::Purple, false, 0.5f, 10, 10);
}

void ATankController::SetPawn(APawn* InPawn)
{
	Super::SetPawn(InPawn);

	TankPawn = Cast<ATankPawn>(InPawn);
}

void ATankController::MoveForward(float Value)
{
	TankPawn->MoveForward(Value);
}

void ATankController::MoveRight(float Value)
{
	TankPawn->MoveRight(Value);
}

void ATankController::RotateRight(float Value)
{
	TankPawn->RotateRight(Value);
}

ATankController::ATankController()
{
	bShowMouseCursor = true;
}
