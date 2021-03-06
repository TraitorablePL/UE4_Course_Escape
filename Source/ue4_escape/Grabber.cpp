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

	GrabbedObjectMovement();
}

void UGrabber::GrabbedObjectMovement()
{
	if (!PhysicsHandler) {
		PhysicsHandlerError();
		return;
	}

	if (PhysicsHandler->GetGrabbedComponent())
	{
		//Changing grabbed object position each tick
		PhysicsHandler->SetTargetLocation(GetLineTracers().v2);
	}
}

void UGrabber::BindActionsToInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent) {
		InputComponent->BindAction(TEXT("Grab"), IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction(TEXT("Grab"), IE_Released, this, &UGrabber::Release);
	}
	else {
		InputComponentError();
		return;
	}
}

void UGrabber::FindPhysicsHandlerComponent()
{
	PhysicsHandler = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (!PhysicsHandler) {
		PhysicsHandlerError();
		return;
	}
}

FHitResult UGrabber::DetectObjectInOurReach()
{
	FHitResult RaycastHit;
	FCollisionQueryParams TraceParameters(FName(TEXT("")), false, GetOwner());

	//Ray-cast trace and detect it's collision with PhysicsBody
	GetWorld()->LineTraceSingleByObjectType(
		OUT RaycastHit,
		GetLineTracers().v1,
		GetLineTracers().v2,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParameters
	);

	//DrawDebugLine(GetWorld(), PlayerViewPointLocation, LineTraceEnd, FColor(0, 0, 255), false, 0, 0, 1);
	return RaycastHit;
}

FTwoVectors UGrabber::GetLineTracers() {

	FVector ViewPointLocation;
	FRotator ViewPointRotation;
	FTwoVectors LineTracers;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT ViewPointLocation,
		OUT ViewPointRotation
	);

	LineTracers.v1 = ViewPointLocation;
	LineTracers.v2 = LineTracers.v1 + ViewPointRotation.Vector()*LineTraceReach;

	return LineTracers;
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab key is pressed"))

	if (!PhysicsHandler) { 
		PhysicsHandlerError();
		return;
	}

	AActor *GrabbedActor = DetectObjectInOurReach().GetActor();

	if (GrabbedActor) {
		UPrimitiveComponent *GrabbedComponent = DetectObjectInOurReach().GetComponent();

		//Calculating center point of grabbed object
		FVector ObjectLocation = DetectObjectInOurReach().GetActor()->GetActorLocation();
		FVector HalfHeightLocation = FVector(0,0,GrabbedActor->GetComponentsBoundingBox().GetCenter().Z);

		FVector GrabLocation = ObjectLocation + HalfHeightLocation;
		FRotator GrabRotation = DetectObjectInOurReach().GetActor()->GetActorRotation();

		PhysicsHandler->GrabComponentAtLocationWithRotation(GrabbedComponent, NAME_None, GrabLocation, GrabRotation);
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab key is released"))

	if (!PhysicsHandler) {
		PhysicsHandlerError();
		return;
	}

	PhysicsHandler->ReleaseComponent();
}

void UGrabber::PhysicsHandlerError()
{
	UE_LOG(LogTemp, Error, TEXT("Cannot find UPhysicsHandlerComponent for %s"), *GetOwner()->GetName())
}

void UGrabber::InputComponentError()
{
	UE_LOG(LogTemp, Error, TEXT("Cannot find UInputComponent for %s"), *GetOwner()->GetName())
}