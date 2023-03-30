// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"


void ATower::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this,0));
	GetWorldTimerManager().SetTimer(FireTimerHandle,this,&ATower::CheckFireCondition,FireRate,true,0);
}

void ATower::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Tank)
	{

		if (IsPlayerInRange())
		{
			RotateTurret(Tank->GetActorLocation());
		}
	}
	
	
}

void ATower::HandleDestruction()
{
	Super::HandleDestruction();
	Destroy();
}

void ATower::CheckFireCondition()
{

	if (IsPlayerInRange())
	{
		Fire();
	}
}

bool ATower::IsPlayerInRange() const
{
	return FVector::Dist(GetActorLocation(), Tank->GetActorLocation()) <= FireRange;
}

