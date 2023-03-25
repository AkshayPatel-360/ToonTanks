// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ATank::ATank()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));

	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));
	Camera->SetupAttachment(SpringArm);
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	PlayerControllerRef = Cast<APlayerController>(GetController());
}

void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerControllerRef)
	{
		FHitResult HitResult;
		PlayerControllerRef->GetHitResultUnderCursor(ECC_Visibility,false,HitResult);

		DrawDebugSphere(GetWorld(),HitResult.ImpactPoint,12,12,FColor::Cyan,false,-1);

		RotateTurret(HitResult.ImpactPoint);
	}
	
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"),this,&ATank::Move);
	PlayerInputComponent->BindAxis(TEXT("Turn"),this,&ATank::Turn);
}





void ATank::Move(float Value)
{
	FVector Movement = FVector(Value , 0.f, 0.f);
	AddActorLocalOffset(Movement * MoveSpeed * GetWorld()->GetDeltaSeconds(), true);
}


void ATank::Turn(float Value)
{
	// Calculate the rotation to be applied this frame
	float RotationThisFrame = Value * TurnSpeed * GetWorld()->GetDeltaSeconds();

	// Apply the rotation to the tank
	AddActorLocalRotation(FRotator(0.f, RotationThisFrame, 0.f),true);
}


