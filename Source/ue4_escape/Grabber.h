// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/InputComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "DrawDebugHelpers.h"
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4_ESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UGrabber();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	//Value that determines how far we can reach objects
	float LineTraceReach = 200.0;

	UPhysicsHandleComponent *PhysicsHandler = nullptr;
	UInputComponent *InputComponent = nullptr;

	//Perform object grabbing action
	void Grab();

	//Perform object releasing action
	void Release();

	//Setup input actions
	void BindActionsToInputComponent();

	//Find if any physics handle component is attached to object
	void FindPhysicsHandlerComponent();

	//Update location of grabbed object
	void GrabbedObjectMovement();

	//Check if we're close enough to physics body
	FHitResult DetectObjectInOurReach();

	//Calculate and return Player viewpoint vector with reach vector
	FTwoVectors GetLineTracers();

	void PhysicsHandlerError();

	void InputComponentError();
};