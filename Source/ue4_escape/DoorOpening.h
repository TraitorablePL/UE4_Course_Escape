// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "DoorOpening.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UE4_ESCAPE_API UDoorOpening : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDoorOpening();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	UPROPERTY(EditAnywhere)
	float OpenAngle = 90;

	UPROPERTY(EditAnywhere)
	float CloseAngle = 0;

	UPROPERTY(EditAnywhere)
	float CloseDelay = 1;

	UPROPERTY(EditAnywhere)
	ATriggerVolume *PressurePlate;

	UPROPERTY(VisibleAnywhere)
	AActor *PlayerThatTrigger;

	UPROPERTY(VisibleAnywhere)
	AActor* Owner;

	float LastOpenTime;
	
};
