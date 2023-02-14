// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"
#include "Kismet/KismetSystemLibrary.h"

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
	FString MyString = GetName();
	UE_LOG(LogTemp, Display, TEXT("%s"), *MyString);
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

	if (ShouldPlatformReturn())
	{
		PlatformVelocity *= -1;
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		StartLocation = StartLocation - MoveDirection * MoveDistance;
		SetActorLocation(StartLocation);
	}
	else
	{
		FVector CurrentLocation = GetActorLocation();
		CurrentLocation += PlatformVelocity * DeltaTime;
		SetActorLocation(CurrentLocation);
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	FRotator CurrentRotation = GetActorRotation();
	// This not works because rotater element takes values from -90 to 90
	// CurrentRotation += RotationVelocity * DeltaTime;
	// SetActorRotation(CurrentRotation);

	// AddActorLocalRotation: consider flipping value if exceeding limit
	AddActorLocalRotation(RotationVelocity * DeltaTime);
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
	float MovedDistance = GetMovedDistance();
	return MovedDistance >= MoveDistance;
};

float AMovingPlatform::GetMovedDistance() const
{
	return FVector::Dist(StartLocation, GetActorLocation());
}