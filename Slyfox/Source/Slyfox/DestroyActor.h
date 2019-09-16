// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestroyActor.generated.h"

UCLASS()
class SLYFOX_API ADestroyActor : public AActor
{
	GENERATED_BODY()


public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	ADestroyActor();

	UFUNCTION()
	void OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor);

};
