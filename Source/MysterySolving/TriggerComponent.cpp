// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ShapeComponent.h"
#include "Components/SphereComponent.h"

UTriggerComponent::UTriggerComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}
// Called when the game starts
void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
    UE_LOG(LogTemp, Display, TEXT("BeginPlay OK"));
}
void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    
    AActor* getAcceptableAtor = GetAcceptableActor();
    UE_LOG(LogTemp, Display, TEXT("isItemSwitchJudge: %s"), isItemSwitchJudge ? TEXT("True") : TEXT("False"));
    UE_LOG(LogTemp, Display, TEXT("getAcceptableAtor: %s"), getAcceptableAtor ? TEXT("Valid") : TEXT("nullptr"));

    TArray<AActor*> actors;
    GetOverlappingActors(actors);
    for(AActor* actor : actors)
    {
        if(IsOverlappingActor(actor))
        {
            if(getAcceptableAtor != nullptr)
            {
                if(isItemSwitchJudge)
                {
                    for(AActor *doorActor : doorActors)
                    {
                        doorComponent = doorActor->FindComponentByClass<UDoorMover>();
                        if(doorComponent != nullptr)
                        {
                            doorComponent->SetShouldMove(!doorComponent->shouldMove);
                            UE_LOG(LogTemp, Display, TEXT("True"));
                        }
                    }
                    isItemSwitchJudge =false;
                }
            }
        }
    }
    if(getAcceptableAtor == nullptr)
    {
        if(!isItemSwitchJudge)
        {
            for(AActor *doorActor : doorActors)
            {
                doorComponent = doorActor->FindComponentByClass<UDoorMover>();
                if(doorComponent != nullptr)
                {
                    doorComponent->SetShouldMove(!doorComponent->shouldMove);
                    UE_LOG(LogTemp, Display, TEXT("false"));
                }
            }
            isItemSwitchJudge = true;
        }
    }
    // GetOverlappingActors(actors);
    // bool isOverlapping = (actors.Num() > 0);
    // AActor* getAcceptableAtor = GetAcceptableActor();
    // if(getAcceptableAtor != nullptr && isOverlapping)
    // {
    //     if(isItemSwitchJudge)
    //     {
    //         for(AActor *doorActor : doorActors)
    //         {
    //             doorComponent = doorActor->FindComponentByClass<UDoorMover>();
    //             if(doorComponent != nullptr)
    //             {
    //                 doorComponent->SetShouldMove(!doorComponent->shouldMove);
    //                 UE_LOG(LogTemp, Display, TEXT("True"));
    //             }
    //         }
    //         isItemSwitchJudge = false;
    //     }
    // }
    // else if(getAcceptableAtor == nullptr && !isOverlapping)
    // {
    //     if(!isItemSwitchJudge)
    //     {
    //         for(AActor* doorActor : doorActors)
    //         {
    //             doorComponent = doorActor->FindComponentByClass<UDoorMover>();
    //             if(doorComponent != nullptr)
    //             {
    //                 doorComponent->SetShouldMove(!doorComponent->shouldMove);
    //                 UE_LOG(LogTemp, Display, TEXT("false"));
    //             }
    //         }
    //         isItemSwitchJudge = true;
    //     }
    // }
}
AActor* UTriggerComponent::GetAcceptableActor()
{
    TArray<AActor*> actors;
    GetOverlappingActors(actors);
    for(AActor* actor : actors)
    {
        bool hasAcceptableTag = actor->ActorHasTag(acceptableActorTag);
        bool isGrabbed = actor->ActorHasTag("Grabbed");
        if(hasAcceptableTag && !isGrabbed)
        {
            return actor;
        }
    }
    return nullptr;
}