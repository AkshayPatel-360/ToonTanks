// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:

	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditAnywhere,Category = "Movement")
	float MoveSpeed = 200;

	UPROPERTY(EditAnywhere,Category = "Movement")
	float TurnSpeed = 200;

	UPROPERTY(VisibleAnywhere,Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere,Category = "Components")
	class UCameraComponent* Camera;

	void Move(float Value);
	void Turn(float Value);

	UPROPERTY()
	APlayerController* PlayerControllerRef; 
	
	
};


