// Fill out your copyright notice in the Description page of Project Settings.

#include "DoorOpening.h"

#define OUT


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

	// ...
}

// Called every frame
void UDoorOpening::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (GetTotalMassOnPressurePlate()>ActivationMass)
	{
		OnOpen.Broadcast();
	}
	else
	{
		OnClose.Broadcast();
	}
}

float UDoorOpening::GetTotalMassOnPressurePlate()
{
	float TotalMass = 0.0f;
	TArray<AActor*> ActorsOnPressurePlate;

	if (!PressurePlate) {
		UE_LOG(LogTemp, Error, TEXT("PressurePlate for %s is not assigned"), *GetOwner()->GetName())
		return TotalMass;
	}

	PressurePlate->GetOverlappingActors(OUT ActorsOnPressurePlate);

	for (const auto* Actor:ActorsOnPressurePlate) {
		TotalMass+=Actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return TotalMass;
}