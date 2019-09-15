// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Elevator.generated.h"

UENUM()
enum class DevAxis : uint8
{
	X,
	Y,
	Z
};

UCLASS()
class SLYFOX_API AElevator : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AElevator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void AfterDelayFunction();

	UFUNCTION(BlueprintCallable)
	void AfterMovementFunction();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float ElevatorSpeed;

	UPROPERTY(EditAnywhere)
	float Distance;

	UPROPERTY(EditAnywhere)
	DevAxis MovementAxis;

	UPROPERTY(EditAnywhere)
	float DelayTime;

private:
	FLatentActionInfo MovementInfo;

	FVector placed_location;
	FVector destination;
	
	bool on_delay = false;
	bool is_moving = false;
};
