// Fill out your copyright notice in the Description page of Project Settings.


#include "Cannon.h"
#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Engine/Engine.h"

// Sets default values
ACannon::ACannon()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CannonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CannonMesh"));
	RootComponent = CannonMesh;

	ProjectileSpawnpoint = CreateDefaultSubobject<UArrowComponent>(TEXT("ProjectileSpawnpoint"));
	ProjectileSpawnpoint->SetupAttachment(CannonMesh);
}


void ACannon::Fire()
{
	if (!bCanFire || patron == 0)
	{
		return;
	}
	bCanFire = false;
	Patroni();
	if (CannonType == ECannonType::FireProjectile)
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire Projectile")));
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Red, FString::Printf(TEXT("Fire Trace")));
	}

	GetWorld()->GetTimerManager().SetTimer(ReloadTimer, this, &ACannon::Reload, ReloadTime, false);
}

void ACannon::Patroni()
{
	GetWorld()->GetTimerManager().ClearTimer(TimerPatronov);
	bCanFire = true;
	netpatroni = 0;
	patron--;
	GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Blue, FString::Printf(TEXT("Patronov:%d"), patron));
	return;
}

void ACannon::Reload()
{
	bCanFire = true;
}

