// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorOpening.h"
#include "Engine/World.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"


// Sets default values for this component's properties
UDoorOpening::UDoorOpening()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UDoorOpening::BeginPlay()
{
	Super::BeginPlay();	

	Owner = GetOwner();
	PlayerThatTrigger = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UDoorOpening::OpenDoor()
{
	Owner->SetActorRotation(FRotator(0, OpenAngle, 0));
}

void UDoorOpening::CloseDoor()
{
	Owner->SetActorRotation(FRotator(0, CloseAngle, 0));
}


// Called every frame
void UDoorOpening::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate->IsOverlappingActor(PlayerThatTrigger))
	{
		OpenDoor();
		LastOpenTime = GetWorld()->GetTimeSeconds();
	}
	else
	{
		float CurrentTimeSecs = GetWorld()->GetTimeSeconds();
		if (CurrentTimeSecs - LastOpenTime > CloseDelay) {
			CloseDoor();
		}
	}

}

