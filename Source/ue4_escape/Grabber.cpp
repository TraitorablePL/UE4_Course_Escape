// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"

#define OUT

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	FindPhysicsHandlerComponent();

	BindActionsToInputComponent();

}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandler->GetGrabbedComponent()) 
	{
		//TODO Refactoring
		//same in DetectObjectInOurReach
		FVector PlayerViewPointLocation;
		FRotator PlayerViewPointRotation;

		FVector LineTraceEnd;

		FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

		GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
			OUT PlayerViewPointLocation,
			OUT PlayerViewPointRotation
		);

		//Calculate at what position line trace end will be
		LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector()*LineTraceReach;

		//Changing grabbed object position each tick
		PhysicsHandler->SetTargetLocation(LineTraceEnd);
	}
}

void UGrabber::BindActionsToInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent) {
		UE_LOG(LogTemp, Warning, TEXT("UInputComponent is operational for %s"), *GetOwner()->GetName())

		InputComponent->BindAction(TEXT("Grab"), IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction(TEXT("Grab"), IE_Released, this, &UGrabber::Release);
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Cannot find UInputComponent for %s"), *GetOwner()->GetName())
	}
}

void UGrabber::FindPhysicsHandlerComponent()
{
	PhysicsHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandler) {
		UE_LOG(LogTemp, Warning, TEXT("UPhysicsHandlerComponent is operational for %s"), *GetOwner()->GetName())
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("Cannot find UPhysicsHandlerComponent for %s"), *GetOwner()->GetName())
	}
}


FHitResult UGrabber::DetectObjectInOurReach()
{
	FHitResult RaycastHit;

	//TODO Refactoring
	//same in TickComponent
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;
	
	FVector LineTraceEnd;

	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	//Calculate at what position line trace end will be
	LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector()*LineTraceReach;

	//DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(0, 0, 255), false, 0, 0, 1);

	//Ray-cast trace and detect it's collision with PhysicsBody
	GetWorld()->LineTraceSingleByObjectType(
		OUT RaycastHit,
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	AActor *ActorHit = RaycastHit.GetActor();

	//When Unreal tries to write the result of Raycasting while noting is pointed, editor is crashing
	if (ActorHit) {
		UE_LOG(LogTemp, Warning, TEXT("Pointing at %s"), *ActorHit->GetName())
	}
	return RaycastHit;
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab key is pressed"))

	AActor *GrabbedActor = DetectObjectInOurReach().GetActor();

	if (GrabbedActor) {
		UPrimitiveComponent *GrabbedComponent = DetectObjectInOurReach().GetComponent();

		GrabbedActor->GetComponentsBoundingBox().GetCenter();
		//Calculating center point of grabbed object
		FVector ObjectLocation = DetectObjectInOurReach().GetActor()->GetActorLocation();
		FVector HalfHeightLocation = FVector(0,0,GrabbedActor->GetComponentsBoundingBox().GetCenter().Z);
		FVector GrabLocation = ObjectLocation + HalfHeightLocation;

		PhysicsHandler->GrabComponent(GrabbedComponent, NAME_None, GrabLocation, true);
	}
}
	

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab key is released"))

	PhysicsHandler->ReleaseComponent();
}

