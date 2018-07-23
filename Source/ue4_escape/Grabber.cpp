// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
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

	
	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	float LineTraceReach = 100.0;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerViewPointLocation, PlayerViewPointRotation);

	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector()*LineTraceReach;

	DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(0, 0, 255), false, 0, 0, 1);

	FString PlayerViewPointLocationText = PlayerViewPointLocation.ToString();
	FString PlayerViewPointRotationText = PlayerViewPointRotation.ToString();
	UE_LOG(LogTemp, Warning, TEXT("Viewport location: %s, rotation: %s"), 
		*PlayerViewPointLocationText, 
		*PlayerViewPointRotationText
	)
	// ...
}

