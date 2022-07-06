// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include <Components/StaticMeshComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>

// Sets default values
ATankPawn::ATankPawn()
{

	PrimaryActorTick.bCanEverTick = true;

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BodyMesh"));
	RootComponent = BodyMesh;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TurretMesh"));
	TurretMesh->SetupAttachment(BodyMesh);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(BodyMesh);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}
  
void ATankPawn::MoveForward(float Value)
{
	TargetAxisValue = Value;
}

void ATankPawn::MoveRight(float Value)
{
	TargetRightAxisValue = Value;
}

void ATankPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector CurrentLocation = GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	FVector RightVector = GetActorRightVector();
<<<<<<< HEAD
	FVector movePosition = CurrentLocation + (ForwardVector * MoveSpeed * TargetAxisValue) + (RightVector * MoveSpeed * TargetRightAxisValue);
=======
	FVector movePosition = CurrentLocation + ForwardVector * MoveSpeed * TargetAxisValue + (RightVector * MoveSpeed * TargetRightAxisValue);
>>>>>>> main
	SetActorLocation(movePosition, true);
}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();

	SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, 0.0f));
}
