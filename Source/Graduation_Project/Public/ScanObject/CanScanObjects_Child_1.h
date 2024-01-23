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

public:
	ACanScanObjects_Child_1(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Collision")
	class UBoxComponent* BoxCollision;


	// 声明碰撞开始的事件函数
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// 声明碰撞结束的事件函数
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
