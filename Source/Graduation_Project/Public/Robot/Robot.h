// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Robot.generated.h"


class URobotMovementComponent;


UENUM()
enum RobotState
{
	Idle,
	Moveing,
	PlayerControlMove
};



// 使用std命名空间，或者在使用std::pair的地方加上std::前缀
using namespace std;

UCLASS()
class GRADUATION_PROJECT_API ARobot : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ARobot(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UCharacterMovementComponent* MovementComponent;


#pragma region FollowPlayer
public:
	class AExplorer* Player;
	class ARobot_AIController* Robot_AIController;


	UFUNCTION(BlueprintCallable, Category = "My Function")
	void SetRobotFollowPlayerSpeed();
#pragma endregion

#pragma region AI Algrithm
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "RobotMovementComponent")
	URobotMovementComponent* RobotMovementComponent;

	UPROPERTY(BlueprintReadWrite, Category = "Robot")
	TEnumAsByte<RobotState> CurrentState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "About RobotMove")
	float Move_Threshold = 200.f;

	FVector MoveSpecifyLocation;

	void LookAtPlayer();

	void LookSpecifyLocation(const FVector& SpecifyLocation);

	void LookAtSpecifyLocation(const FVector& SpecifyLocation);

	void MoveToPlayerLocation();

	void MoveToSpecifyLocation(const FVector& SpecifyLocation);

	void RobotScanObjects(const FVector& ScanLocation);
#pragma endregion

};
