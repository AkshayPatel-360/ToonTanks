// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()

public:

	virtual void Tick(float DeltaTime) override;

	void HandleDestruction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY()
	class ATank* Tank;

	UPROPERTY(EditAnywhere,Category = "Combat")
	float FireRange = 800;

	FTimerHandle FireTimerHandle;
	float FireRate = 2;
	void CheckFireCondition();

	bool IsPlayerInRange() const;
	
};
