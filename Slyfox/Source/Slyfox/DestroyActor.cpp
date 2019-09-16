// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyActor.h"


// Sets default values
// add a mesh in the editor and set Collision Presets to Trigger
ADestroyActor::ADestroyActor()
{
	OnActor.AddDynamic(this, &ADestroyActor::OnOverlap);
}

void ADestroyActor::OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor)
{
	Destroy();
}