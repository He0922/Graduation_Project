// Fill out your copyright notice in the Description page of Project Settings.


#include "Robot/Robot.h"
#include "Graduation_Project/Public/Explorer.h"
#include "Kismet/GameplayStatics.h"
#include "Graduation_Project/DebugHelper.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Robot/Robot_AIController.h"
#include "MovementComponent/RobotMovementComponent.h"


// Sets default values
ARobot::ARobot(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.SetDefaultSubobjectClass<URobotMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RobotMovementComponent = Cast<URobotMovementComponent>(GetMovementComponent());
}

// Called when the game starts or when spawned
void ARobot::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<AExplorer>(UGameplayStatics::GetActorOfClass(GetWorld(), AExplorer::StaticClass()));
	MovementComponent = this->GetCharacterMovement();
	MovementComponent->GravityScale = 0.f;
	MovementComponent->SetMovementMode(EMovementMode::MOVE_Flying);

	Robot_AIController = Cast<ARobot_AIController>(this->GetController());



	
}

// Called every frame
void ARobot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (Player->Camera_OutLineTraceHitResult.IsValidIndex(0))
	{
		MoveSpecifyLocation = Player->MouseClickLocation;
	}

	if (!Player->RobotMoveToSpecifyLocation)
	{
		MoveToPlayerLocation();
	}
	else if (Player->RobotMoveToSpecifyLocation && Player->Camera_OutLineTraceHitResult.IsValidIndex(0))
	{
		MoveToSpecifyLocation(MoveSpecifyLocation);
	}

	

}

// Called to bind functionality to input
void ARobot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


#pragma region AI Algrithm
void ARobot::SetRobotSpeed()
{
}
void ARobot::LookAtPlayer()
{
	FVector PlayerLocation = Player->GetActorLocation();
	FVector RobotLocation = this->GetActorLocation();
	
	FRotator RobotRotation = UKismetMathLibrary::FindLookAtRotation(RobotLocation, PlayerLocation);

	SetActorRotation(RobotRotation);
}

void ARobot::LookAtSpecifyLocation(const FVector& SpecifyLocation)
{
	const FVector RobotLocation = this->GetActorLocation();

	FRotator RobotRotation = UKismetMathLibrary::FindLookAtRotation(RobotLocation, SpecifyLocation);

	SetActorRotation(RobotRotation);
}

void ARobot::MoveToPlayerLocation()
{
	if (!Player->RobotMoveToSpecifyLocation)
	{
		LookAtPlayer();

		// 获取Robot和玩家的位置以及Robot向前的向量
		const FVector PlayerLocation = Player->GetActorLocation();
		const FVector RobotLocation = this->GetActorLocation();

		// 计算Robot与Player之间的距离
		float Distance = (PlayerLocation - RobotLocation).Size();

		// 定义一个容差值，表示Robot和Player之间的最小距离
		const float Tolerance = 100.f;

		if (Distance > Move_Threshold + Tolerance)
		{
			// 计算朝向玩家位置所需旋转角度，将玩家位置的Z坐标替换为Robot位置的Z坐标
			FVector PlayerLocationWithRobotZ = FVector(PlayerLocation.X + 100.f, PlayerLocation.Y, RobotLocation.Z);
			FRotator FaceToPlayerRotation = UKismetMathLibrary::FindLookAtRotation(RobotLocation, PlayerLocationWithRobotZ);

			// 更新Robot朝向
			this->SetActorRotation(FaceToPlayerRotation);

			// 根据蓝图，添加一个单位向量来移动Robot朝着玩家方向移动
			AddMovementInput(PlayerLocationWithRobotZ - RobotLocation, 1.f, true);
		}
	}
}

void ARobot::MoveToSpecifyLocation(const FVector& SpecifyLocation)
{
	if(Player->RobotMoveToSpecifyLocation)
	{
		LookAtSpecifyLocation(SpecifyLocation);

		// 获取机器人的位置
		const FVector RobotLocation = this->GetActorLocation();

		// 计算指定位置和机器人之间的距离
		float Distance = (SpecifyLocation - RobotLocation).Size();

		const float Threshold = 100.f;

		if (Distance > Move_Threshold + Threshold)
		{
			FVector SpecifyLocationWithRobotZ = FVector(SpecifyLocation.X + 100.f, SpecifyLocation.Y, SpecifyLocation.Z + 100.f);
			FRotator FaceToSpecifyLocation = UKismetMathLibrary::FindLookAtRotation(RobotLocation, SpecifyLocationWithRobotZ);


			this->SetActorRotation(FaceToSpecifyLocation);

			AddMovementInput(SpecifyLocationWithRobotZ - RobotLocation, 1.f, true);
		}
	}
}

#pragma endregion


