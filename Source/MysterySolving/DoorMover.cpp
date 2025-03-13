// Fill out your copyright notice in the Description page of Project Settings.


#include "DoorMover.h"
#include "Math/UnrealMathUtility.h"

// Sets default values for this component's properties
UDoorMover::UDoorMover()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorMover::BeginPlay()
{
	Super::BeginPlay();
	originalLocation = GetOwner()->GetActorLocation();
	openDoorOfset = FVector(originalLocation.X,originalLocation.Y,originalLocation.Z + openDoorTransformLocationZ);
	closeDoorOfset = FVector(originalLocation.X,originalLocation.Y,originalLocation.Z + closeDoorTransformLocationZ);
	// ...
	
}


// Called every frame
void UDoorMover::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	targetLocation = shouldMove ? openDoorOfset = FVector(originalLocation.X,originalLocation.Y,openDoorTransformLocationZ) : closeDoorOfset = FVector(originalLocation.X,originalLocation.Y,closeDoorTransformLocationZ);
	FVector currentLocation = GetOwner()->GetActorLocation();
	speed = (targetLocation - currentLocation).Length() / moveTime;

	FVector newLocation = FMath::VInterpConstantTo(currentLocation,targetLocation,DeltaTime,speed);
	GetOwner()->SetActorLocation(newLocation);

	// ...
}
void UDoorMover::SetShouldMove(bool openClose)
{
	shouldMove = openClose;
}

