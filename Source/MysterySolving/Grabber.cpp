// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	// UPhysicsHandleComponent* PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	// if(PhysicsHandle != nullptr)
	// {
	// 	UE_LOG(LogTemp, Display, TEXT("Got Pyhsics Handle: %s"), *PhysicsHandle->GetName());
	// }
	// else
	// {
	// 	UE_LOG(LogTemp, Display, TEXT("No Pyhsics Found!"));
	// }

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent *physicsHandle = GetPhysicsHandle();
	if (physicsHandle && physicsHandle->GetGrabbedComponent())
	{
		FVector targetLocation = GetComponentLocation() + GetForwardVector() * holdDistance;
		physicsHandle->SetTargetLocationAndRotation(targetLocation,GetComponentRotation());
	}
	
	// ...
}
void UGrabber::Grab()
{
	
	UPhysicsHandleComponent *physicsHandle = GetPhysicsHandle();
	if(physicsHandle == nullptr){
		return;
	}
	FHitResult hitResult;
	bool hasHit = GetGrabberbleInReach(hitResult);
	if(hasHit){
		UPrimitiveComponent* hitComponent = hitResult.GetComponent();
		hitComponent->SetSimulatePhysics(true);
		hitComponent->WakeAllRigidBodies();
		AActor* hitActor = hitResult.GetActor();
		hitActor->Tags.Add("Grabbed");
		hitActor->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
		physicsHandle->GrabComponentAtLocationWithRotation(
			hitComponent,
			NAME_None,
			hitResult.ImpactPoint,
			GetComponentRotation()
		);
	}
}
void UGrabber::Release()
{
	UPhysicsHandleComponent* physicsHandle = GetPhysicsHandle();
	if(physicsHandle && physicsHandle->GetGrabbedComponent())
	{
		AActor* grabberActor = physicsHandle->GetGrabbedComponent()->GetOwner();
		grabberActor->Tags.Remove("Grabbed");
		physicsHandle->ReleaseComponent();
	}
}
UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if(result == nullptr)
	{
		UE_LOG(LogTemp, Display, TEXT("Grabber requies a UPhysicsHandleComponent,"));
	}
	return result;
}

bool UGrabber::GetGrabberbleInReach(FHitResult& outHitResult) const
{
	FVector start = GetComponentLocation();
	FVector end = start + GetForwardVector() * maxGrabDistance;
	DrawDebugLine(GetWorld(), start, end, FColor::Red);
	DrawDebugSphere(GetWorld(), end, 10, 10, FColor::Blue, false, 5);

	FCollisionShape Sphere = FCollisionShape::MakeSphere(grablRedius);
	return GetWorld()->SweepSingleByChannel(
		outHitResult,
		start, end,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere);

}