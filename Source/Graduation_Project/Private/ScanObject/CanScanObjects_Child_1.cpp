// Fill out your copyright notice in the Description page of Project Settings.


#include "ScanObject/CanScanObjects_Child_1.h"
#include "Components/BoxComponent.h"



ACanScanObjects_Child_1::ACanScanObjects_Child_1(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetBoxExtent(FVector(100.f, 100.f, 50.f));
	BoxCollision->SetupAttachment(GetRootComponent());
}



void ACanScanObjects_Child_1::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACanScanObjects_Child_1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
