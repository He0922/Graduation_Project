// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Robot.generated.h"

// 使用std命名空间，或者在使用std::pair的地方加上std::前缀
using namespace std;

UCLASS()
class GRADUATION_PROJECT_API ARobot : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARobot();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

#pragma region FollowPlayer
public:
	class AExplorer* Player;
	class ARobot_AIController* Robot_AIController;

	UCharacterMovementComponent* MovementComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "About RobotMove")
	float Move_Threshold = 300.f;

	bool IsMoveing;

	UFUNCTION(BlueprintCallable, Category = "My Function")
	void SetRobotSpeed();
#pragma endregion

#pragma region AI Algrithm
	void LookAtPlayer();

	void MoveToPlayerLocation();
#pragma endregion

};
