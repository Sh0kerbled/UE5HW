// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameStructs.h"
#include "GameFramework/Actor.h"
#include "Cannon.generated.h"


UCLASS()
class TANKOGEDDON_API ACannon : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
		UStaticMeshComponent* CannonMesh;
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	class UArrowComponent* ProjectileSpawnpoint;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
	ECannonType CannonType;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Components")
		float ReloadTime = 1.0f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "patroni")
	int patron = 30;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "patroni")
	int bs = 10;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "patroni")
	float interval = 0.5f;
	FTimerHandle ReloadTimer;
	FTimerHandle TimerPatronov;
public:
	ACannon();
	void Fire();
	void Reload();
	void FireSpecial();
private:
	bool bCanFire = true;

	int netpatroni = 0;

	void Patroni();
};
