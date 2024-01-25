// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ScanObject/CanScanObjects.h"
#include "C_CanScanObjects_Text.generated.h"

/**
 * 
 */
UCLASS()
class GRADUATION_PROJECT_API AC_CanScanObjects_Text : public ACanScanObjects
{
	GENERATED_BODY()
	
public:
	AC_CanScanObjects_Text();

protected:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

#pragma region AboutScan
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BoxCollision")
	class UBoxComponent* BoxCollision_C;

	// 声明碰撞开始的事件函数
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	// 声明碰撞结束的事件函数
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
#pragma endregion

public:

};
