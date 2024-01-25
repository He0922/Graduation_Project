// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"

#include "Explorer.generated.h"


class UCustomMovementComponent;

UCLASS()
class GRADUATION_PROJECT_API AExplorer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AExplorer(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void NotifyActorEndOverlap(AActor* OtherActor) override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CustomMovementComponent")
	UCustomMovementComponent* CustomMovementComponent;

#pragma region PlayerComponent
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpringArm")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpringArm")
	class UCameraComponent* Camera;

#pragma endregion


#pragma region PlayerAction
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MappingContext")
	class UInputMappingContext* Action_MappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* Move_Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* Look_Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* Jump_Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* ControlRobotMove;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* RobotFollowPlayer_Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* ScanObjects;


	// 判断机器人是移动到指定位置还是跟随人物移动
	bool bRobotFollowPlayer = true;

	bool bRobotMoveSpecifyLocation = false;
	FVector MouseClickLocation;




	void Move_Function(const FInputActionValue& Value);
	void Look_Function(const FInputActionValue& Value);
	void Control_RobotMove(const FInputActionValue& Value);
	void RobotFollowPlayer(const FInputActionValue& Value);
	void RobotScanObjects(const FInputActionValue& Value);
#pragma endregion


#pragma region Forceinline
	FORCEINLINE UCustomMovementComponent* GetCustomMovementComponent() const { return CustomMovementComponent; }
#pragma endregion


#pragma region Camera
	TArray<FHitResult> Camera_OutLineTraceHitResult;
	bool bCameraTraceHit;

	void CameraTrace(const FVector& Start, const FVector& End);
	void CameraTrace_Start_End();

	


#pragma endregion


#pragma region AboutScan
	// 存储Capsule碰撞的Actor
	AActor* Capsule_CollisionActor;
	// 存储射线检测命中的对象Actor
	AActor* LT_HitActor;

	// 判断机器人是否在进行扫描物体人物
	bool bRemoteRobotScanObjects = false;
	bool bCloserRangeRobotScanObjects = false;

	bool bCapsuleCollision = false;


	// 存储射线命中的物体的Tag
	TArray<FName> LT_HitActorTags;

	// 存储Capsule的碰撞的物体的Tag
	TArray<FName> CollisionActorTags;


	FVector LT_ScanObjectsLocation;
	FVector CapsuleCollisionScanObjectsLocation;
#pragma endregion


public:
	class ARobot* Robot;
};
