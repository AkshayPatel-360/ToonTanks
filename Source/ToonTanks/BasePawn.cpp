// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"

#include "Projectile.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::HandleDestruction()
{
	// TODO : Visual/sound

	
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector TargetLocation = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator Rotator = FRotator(0, TargetLocation.Rotation().Yaw, 0);

	TurretMesh->SetWorldRotation(FMath::RInterpTo
		(TurretMesh->GetComponentRotation(), Rotator,
		 GetWorld()->DeltaTimeSeconds, 15));
}

void ABasePawn::Fire()
{
	FVector FireProjectileSpawnPoint = ProjectileSpawnPoint->GetComponentLocation();

	//DrawDebugSphere(GetWorld(),FireProjectileSpawnPoint,16,12,FColor::Red,false,3);

	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();
	
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
	Projectile->SetOwner(this);

}
