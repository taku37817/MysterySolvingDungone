// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"

#include "Grabber.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYSTERYSOLVING_API UGrabber : public USceneComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

	UFUNCTION(BlueprintCallable)
	void Release();

	UFUNCTION(BlueprintCallable)
	void Grab();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	UPROPERTY(EditAnywhere)
	float maxGrabDistance = 400;
	UPROPERTY(EditAnywhere)
	float grablRedius = 100;
	UPROPERTY(EditAnywhere)
	float holdDistance = 200;
	UPROPERTY(EditAnywhere)
	FName setDelActorTag;
	bool GetGrabberbleInReach(FHitResult& outHitResult) const;
	UPhysicsHandleComponent* GetPhysicsHandle() const;
		
};
