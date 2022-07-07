// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankPawn.generated.h"
class UStaticMeshComponent;

UCLASS()
class TANKOGEDDON_API ATankPawn : public APawn
{
	GENERATED_BODY()

public:
	ATankPawn();

	void MoveForward(float Value);

	void MoveRight(float Value);

	void RotateRight(float Value);

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
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
		float MoveSpeed = 30.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
		float RotationSpeed = 10.0f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement")
		float InterpoLatoinKey = 0.1f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite,Category = "TurretRotation")
		float TurretRotationInterpolationKey = 0.5f;
	UPROPERTY()
		class ATankController* TankController;
private:
	float TargetAxisValue = 0.0f;
	float TargetRightAxisValue = 0.0f;
	float RotateRightAxisValue = 0.0f;
};
