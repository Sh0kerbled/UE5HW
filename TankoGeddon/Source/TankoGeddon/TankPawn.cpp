// Fill out your copyright notice in the Description page of Project Settings.


#include "TankPawn.h"
#include <Components/StaticMeshComponent.h>
#include <GameFramework/SpringArmComponent.h>
#include <Camera/CameraComponent.h>
#include "TankController.h"
#include "Kismet/KismetMathLibrary.h"
#include <Components/ArrowComponent.h>

DECLARE_LOG_CATEGORY_EXTERN(TankLog, All, All);
DEFINE_LOG_CATEGORY(TankLog);

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

	CannonSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Cannon setuppoint"));
	CannonSetupPoint->AttachToComponent(TurretMesh, FAttachmentTransformRules::KeepRelativeTransform);

}

void ATankPawn::MoveForward(float Value)
{
	TargetAxisValue = Value;
}

void ATankPawn::MoveRight(float Value)
{
	TargetRightAxisValue = Value;
}

void ATankPawn::RotateRight(float Value)
{
	RotateRightAxisValue = Value;
}

void ATankPawn::Fire()
{
	if (Cannon)
	{
		Cannon->Fire();
	}
}

void ATankPawn::FireSpecial()
{
	Cannon->FireSpecial();
}

void ATankPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	FVector CurrentLocation = GetActorLocation();
	FVector ForwardVector = GetActorForwardVector();
	FVector RightVector = GetActorRightVector();
	FVector movePosition = CurrentLocation + ForwardVector * MoveSpeed * TargetAxisValue + (RightVector * MoveSpeed * TargetRightAxisValue);
	SetActorLocation(movePosition, true);

	CurrentRotateAxisValue = FMath::Lerp(CurrentRotateAxisValue, RotateRightAxisValue, TurretRotationInterpolationKey);
		
	UE_LOG(LogTemp, Warning, TEXT("PovorachivanieNaverno = %f PravoLevoIliKakTam = %f"), RotateRightAxisValue, TargetRightAxisValue);

	float YawRotation = RotationSpeed * CurrentRotateAxisValue * DeltaSeconds;
	FRotator CurrentRotation = GetActorRotation();

	YawRotation = CurrentRotation.Yaw + YawRotation;

	FRotator newRotation = FRotator(0.0f, YawRotation, 0.0f);
	SetActorRotation(newRotation);

	if (TankController)
	{
		FVector MousePos = TankController->GetMousePosition();

		FRotator targetRotation = UKismetMathLibrary::FindLookAtRotation(GetActorLocation(), MousePos);
		FRotator TurretRotation = TurretMesh->GetComponentRotation();
		targetRotation.Pitch = TurretRotation.Pitch;
		targetRotation.Roll = TurretRotation.Roll;

		TurretMesh->SetWorldRotation(FMath::Lerp(TurretRotation, targetRotation, TurretRotationInterpolationKey));
	}
}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();

	//SetActorLocation(FVector(GetActorLocation().X, GetActorLocation().Y, 0.0f));

	TankController = Cast<ATankController>(GetController());

	SetupCannon();
}

void ATankPawn::SetupCannon()
{
	if (CannonClass)
	{
		return;
	}
	if (Cannon)
	{
		Cannon->Destroy();
	}

	FActorSpawnParameters params;
	params.Instigator = this;
	params.Owner = this;
	Cannon = GetWorld()->SpawnActor<ACannon>(CannonClass, params);

	Cannon->AttachToComponent(CannonSetupPoint, FAttachmentTransformRules::SnapToTargetIncludingScale);
}