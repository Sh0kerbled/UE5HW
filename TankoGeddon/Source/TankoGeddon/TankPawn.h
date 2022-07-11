// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Cannon.h"
#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include <Components/ArrowComponent.h>
#include "TankPawn.generated.h"
class UStaticMeshComponent;
class ACannon;
UCLASS()
class TANKOGEDDON_API ATankPawn : public APawn
{
	GENERATED_BODY()

public:
	ATankPawn();

	void MoveForward(float Value);

	void MoveRight(float Value);

	void RotateRight(float Value);

	void Fire(); 

	void FireSpecial();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaSeconds) override;
protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* BodyMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* TurretMesh;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class USpringArmComponent* SpringArm;
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
		class UCameraComponent* Camera;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Turret | Component")
	TSubclassOf<ACannon> CannonClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		UArrowComponent* CannonSetupPoint;
	UPROPERTY()
		class ACannon* Cannon;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
		float MoveSpeed = 100.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
		float RotationSpeed = 10.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
		float InterpoLatoinKey = 0.5f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "TurretRotation")
		float TurretRotationInterpolationKey = 0.5f;
	UPROPERTY()
		class ATankController* TankController;

protected:
	void SetupCannon();


private:
	float TargetAxisValue = 0.0f;
	float TargetRightAxisValue = 0.0f;
	float RotateRightAxisValue = 0.0f;
	float CurrentRotateAxisValue = 0.0f;
};