// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScanObject/CanScanObjects.h"
#include "CanScanObjects_Child_1.generated.h"

/**
 * 
 */
UCLASS()
class GRADUATION_PROJECT_API ACanScanObjects_Child_1 : public ACanScanObjects
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
