// Fill out your copyright notice in the Description page of Project Settings.

/*
My notes

https://answers.unrealengine.com/questions/346556/how-to-setup-the-flatentactioninfo.html?sort=oldest
*/


#include "Elevator.h"
#include "Runtime/Engine/Classes/Kismet/KismetSystemLibrary.h"



// Sets default values
AElevator::AElevator()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AElevator::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("inside begin play"));
	placed_location = GetActorLocation();
	destination = placed_location + Distance;
	//UE_LOG(LogTemp, Warning, TEXT("selected axis %d"), selected_axis);
	//UE_LOG(LogTemp, Warning, TEXT("selected compare to z %s"), (selected_axis == DevAxis::Z ? TEXT("True") : TEXT("False")));

	//Delay
	if (DelayTime > 0.0f)
	{
		on_delay = true;

		FLatentActionInfo DelayInfo;
		DelayInfo.CallbackTarget = this;
		DelayInfo.ExecutionFunction = "AfterDelayFunction";
		DelayInfo.Linkage = 0;
		DelayInfo.UUID = 135;
		
		UKismetSystemLibrary::Delay(this, DelayTime, DelayInfo);
	}

	MovementInfo.CallbackTarget = this;
	MovementInfo.ExecutionFunction = "AfterMovementFunction";
	MovementInfo.Linkage = 0;
	MovementInfo.UUID = 246;
}

void AElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!on_delay)
	{
		FVector current_location = GetActorLocation();
		
		if (!is_moving)
		{
			//UE_LOG(LogTemp, Warning, TEXT("inside condition"));
			is_moving = true;

			USceneComponent* root_component = GetRootComponent();
			FRotator current_rotation = GetActorRotation();

			//UE_LOG(LogTemp, Warning, TEXT("current: %f | placed: %f"), current_location.Z, placed_location.Z);
			//UE_LOG(LogTemp, Warning, TEXT("distance: %f"), Distance);
			//UE_LOG(LogTemp, Warning, TEXT("speed: %f"), ElevatorSpeed);
			
			if (MovementAxis == DevAxis::Z)
			{
				if (current_location.Z == placed_location.Z)
				{
					current_location.Z += Distance;
				}
				else
				{
					current_location.Z -= Distance;
				}
			}
			else if (MovementAxis == DevAxis::Y)
			{
				if (current_location.Y == placed_location.Y)
				{
					current_location.Y += Distance;
				}
				else
				{
					current_location.Y -= Distance;
				}
			}
			else
			{
				if (current_location.X == placed_location.X)
				{
					current_location.X += Distance;
				}
				else
				{
					current_location.X -= Distance;
				}
			}

			UKismetSystemLibrary::MoveComponentTo(root_component, current_location, current_rotation, true, true, ElevatorSpeed, true, EMoveComponentAction::Move, MovementInfo);

			//UE_LOG(LogTemp, Warning, TEXT("outside condition"));
		}
	}
}

/*
// Called every frame
void AElevator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Destroy();
	//FVector2D
	//UE_LOG

	//UKismetSystemLibrary::MoveComponentTo

	//if (!is_moving)
	//{
	//	is_moving = true;
	//}
	
	//UE_LOG(LogTemp, Warning, TEXT("inside tick"));
	FVector current_location = GetActorLocation();
	if (!is_moving)
	{
		UE_LOG(LogTemp, Warning, TEXT("inside condition"));
		is_moving = true;
		
		USceneComponent* root_component = GetRootComponent();
		FRotator current_rotation = GetActorRotation();
		
		
		UE_LOG(LogTemp, Warning, TEXT("current: %f | placed: %f"), current_location.Z, placed_location.Z);
		UE_LOG(LogTemp, Warning, TEXT("distance: %f"), Distance);
		UE_LOG(LogTemp, Warning, TEXT("speed: %f"), ElevatorSpeed);
		if (selected_axis == DevAxis::Z)
		{
			if (current_location.Z == placed_location.Z)
			{
				current_location.Z += Distance;
			}
			else
			{
				current_location.Z -= Distance;
			}
		}
		else if (selected_axis == DevAxis::Y)
		{
			if (current_location.Y == placed_location.Y)
			{
				current_location.Y += Distance;
			}
			else
			{
				current_location.Y -= Distance;
			}
		}
		else
		{
			if (current_location.X == placed_location.X)
			{
				current_location.X += Distance;
			}
			else
			{
				current_location.X -= Distance;
			}
		}
		
		
		FLatentActionInfo info;
		info.CallbackTarget = this;

		UKismetSystemLibrary::MoveComponentTo(root_component, current_location, current_rotation, true, true, ElevatorSpeed, true, EMoveComponentAction::Move, info);

		//is_moving = false;
		UE_LOG(LogTemp, Warning, TEXT("outside condition"));
	}
	else
	{
		if (selected_axis == DevAxis::Z)
		{
			if (current_location.Z == placed_location.Z || current_location.Z == destination.Z)
			{
				is_moving = false;
			}
		}
		else if (selected_axis == DevAxis::Y)
		{
			if (current_location.Y == placed_location.Y || current_location.Y == destination.Y)
			{
				is_moving = false;
			}
		}
		else
		{
			if (current_location.X == placed_location.X || current_location.X == destination.X)
			{
				is_moving = false;
			}
		}
		
	}
}
*/

void AElevator::AfterDelayFunction()
{
	//UE_LOG(LogTemp, Warning, TEXT("after delay"));
	on_delay = false;
}

void AElevator::AfterMovementFunction()
{
	//UE_LOG(LogTemp, Warning, TEXT("after movement"));
	is_moving = false;
}
