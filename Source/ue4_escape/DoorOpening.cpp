// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorOpening.h"
#include "GameFramework/Actor.h"


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

	
}

void UDoorOpening::OpenDoor()
{
	AActor* Owner = GetOwner();

	FRotator DoorRotator = FRotator(0, -75, 0);

	Owner->SetActorRotation(DoorRotator);
}


// Called every frame
void UDoorOpening::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PressurePlate->IsOverlappingActor(PlayerThatTrigger))
	{
		OpenDoor();
	}
}

