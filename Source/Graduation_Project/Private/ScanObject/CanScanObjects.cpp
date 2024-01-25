// Fill out your copyright notice in the Description page of Project Settings.


#include "ScanObject/CanScanObjects.h"
#include "Components/BoxComponent.h"

// Sets default values
ACanScanObjects::ACanScanObjects()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	this->Tags.Add(FName("CanScan"));
}

// Called when the game starts or when spawned
void ACanScanObjects::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACanScanObjects::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

