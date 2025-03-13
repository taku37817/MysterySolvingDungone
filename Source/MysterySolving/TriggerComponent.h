// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "DoorMover.h"

#include "TriggerComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class MYSTERYSOLVING_API UTriggerComponent : public UBoxComponent
{
	GENERATED_BODY()

public:
	UTriggerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	
private:
	// void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	// 	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	// 	bool bFromSweep, const FHitResult& SweepResult);
	// void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	// 	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(EditAnywhere)
	float sphereRadius = 100.0f;
	UPROPERTY(EditAnywhere)
	TArray<AActor*> doorActors;
	UPROPERTY(EditAnywhere)
	FName acceptableActorTag;
	// UPROPERTY(EditAnywhere)
	// FName hitActorTag;
	AActor* GetAcceptableActor();
	
	UDoorMover* doorComponent;
	bool isItemSwitchJudge = true;
};
