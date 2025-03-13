// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DoorMover.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class MYSTERYSOLVING_API UDoorMover : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorMover();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void SetShouldMove(bool openClose);
	UPROPERTY(EditAnywhere)
	bool shouldMove = false;
	
private:
	UPROPERTY(EditAnywhere)
	float moveTime = 2.0f;
	UPROPERTY(EditAnywhere)
	FVector originalLocation;
	UPROPERTY(EditAnywhere)
	FVector openDoorOfset;
	UPROPERTY(EditAnywhere)
	FVector closeDoorOfset;
	UPROPERTY(EditAnywhere)
	float openDoorTransformLocationZ;
	UPROPERTY(EditAnywhere)
	float closeDoorTransformLocationZ;
	FVector targetLocation;
	float speed;
	float currentTime = 0.0f;
	
};
