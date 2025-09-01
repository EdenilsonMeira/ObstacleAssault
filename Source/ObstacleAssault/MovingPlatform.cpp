// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{

	DistanceMoved = GetDistanceMoved();

	if (DistanceMoved >= MoveDistance)
	{
		// The overshoot corrects a small difference in distance can add overtime and set
		// the current location away from its right position on the move back at reach point.

		float Overshoot = DistanceMoved - MoveDistance;

		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		FVector NewStartLocation = StartLocation + MoveDirection * MoveDistance;
		SetActorLocation(NewStartLocation);
		StartLocation = NewStartLocation;

		PlatformVelocity *= -1;
	}
	else
	{
		// Increase X position by 1 each frame
		FVector CurrentLocation = GetActorLocation();

		CurrentLocation += (PlatformVelocity * DeltaTime);

		SetActorLocation(CurrentLocation);

	}
}

float AMovingPlatform::GetDistanceMoved()
{
	return FVector::Dist(StartLocation, GetActorLocation());
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	// Rotate the platform over time

	FRotator RotationToAdd = RotationVelocity * DeltaTime;

	AddActorLocalRotation(RotationToAdd);

}


