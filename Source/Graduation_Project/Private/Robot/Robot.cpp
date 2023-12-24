// Fill out your copyright notice in the Description page of Project Settings.


#include "Robot/Robot.h"
#include "Graduation_Project/Public/Explorer.h"
#include "Kismet/GameplayStatics.h"
#include "Graduation_Project/DebugHelper.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Robot/Robot_AIController.h"

// Sets default values
ARobot::ARobot()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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

	LookAtPlayer();
	MoveToPlayerLocation();

}

// Called to bind functionality to input
void ARobot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


#pragma region FollowPlayer
//AActor* ARobot::GetPlayer() const
//{
//	return Player;
//}
//
//AAIController* ARobot::GetAIController() const
//{
//	return Robot_AIController;
//}
//
//
//float ARobot::CheckDistance()
//{
//	const FVector PlayerLocation = Player->GetActorLocation();
//	const FVector RobotLocation = this->GetActorLocation();
//
//	float Distance = (PlayerLocation - RobotLocation).Size();
//	
//	// Debug::Print(FString::SanitizeFloat(Distance));
//
//	return Distance;
//}
//
//bool ARobot::WhetherFollowPlayer()
//{
//	float Distance = CheckDistance();
//
//	if (Distance > 300.f)
//	{
//		return true;
//	}
//	else
//	{
//		return false;
//	}
//}
//
//void ARobot::SetRobotSpeed()
//{
//	float Distance = CheckDistance();
//	if (Distance > 600.f) 
//	{
//		MovementComponent->MaxFlySpeed = 700.f;
//	}
//	else if (500.f < Distance && Distance < 600.f) 
//	{
//		MovementComponent->MaxFlySpeed = 500.f;
//	}
//	else if (400.f < Distance && Distance < 500.f) 
//	{
//		MovementComponent->MaxFlySpeed = 400.f;
//	}
//	else if (200.f < Distance && Distance < 400.f) 
//	{
//		MovementComponent->MaxFlySpeed = 300.f;
//	}
//	else if (100.f < Distance && Distance < 200.f) 
//	{
//		MovementComponent->MaxFlySpeed = 200.f;
//	}
//
//	// Debug::Print(FString::SanitizeFloat(MovementComponent->GetMaxSpeed()));
//}



#pragma endregion


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
//void ARobot::MoveToPlayerLocation()
//{
//	// ��ȡRobot����ҵ�λ���Լ�Robot��ǰ������
//	const FVector PlayerLocation = Player->GetActorLocation();
//	const FVector RobotLocation = this->GetActorLocation();
//	const FVector RobotForward = this->GetActorForwardVector();
//
//	float RobotLocatino_X = RobotLocation.X;
//	float RobotLocation_Y = RobotLocation.Y;
//	float RobotLocation_Z = RobotLocation.Z;
//
//	float RobotForward_X = RobotForward.X;
//	float RobotForward_Y = RobotForward.Y;
//	float RobotForward_Z = RobotForward.Z;
//
//	float PlayerLocation_X = PlayerLocation.X;
//	float PlayerLocation_Y = PlayerLocation.Y;
//	float PlayerLocation_Z = PlayerLocation.Z;
//
//	// ��ȡRobot��Player֮��ľ���
//	float Distance = (PlayerLocation - RobotLocation).Size();
//
//	// �����볬���ƶ���ֵ��IsMoveing����Ϊtrue
//	if (Distance > Move_Threshold) { IsMoveing = true; }
//	else { IsMoveing = false; }
//
//	FVector NeedMoveToLocation = FVector(PlayerLocation_X, PlayerLocation_Y, RobotForward_Z);
//
//	FRotator FaceToLocation = UKismetMathLibrary::FindLookAtRotation(RobotLocation, NeedMoveToLocation);
//
//	FVector MoveToLocation = FVector(FaceToLocation.Roll, 0.f, FaceToLocation.Roll);
//	
//	AddMovementInput(MoveToLocation, 1.f, true);
//
//}
void ARobot::MoveToPlayerLocation()
{
	// ��ȡRobot����ҵ�λ���Լ�Robot��ǰ������
	const FVector PlayerLocation = Player->GetActorLocation();
	const FVector RobotLocation = this->GetActorLocation();

	// ����Robot��Player֮��ľ���
	float Distance = (PlayerLocation - RobotLocation).Size();

	// �����볬���ƶ���ֵ��IsMoveing����Ϊtrue
	if (Distance > Move_Threshold)
	{
		IsMoveing = true;

		// ���㳯�����λ��������ת�Ƕȣ������λ�õ�Z�����滻ΪRobotλ�õ�Z����
		FVector PlayerLocationWithRobotZ = FVector(PlayerLocation.X+100.f, PlayerLocation.Y, RobotLocation.Z);
		FRotator FaceToPlayerRotation = UKismetMathLibrary::FindLookAtRotation(RobotLocation, PlayerLocationWithRobotZ);

		// ����Robot����
		this->SetActorRotation(FaceToPlayerRotation);

		// ������ͼ�����һ����λ�������ƶ�Robot������ҷ����ƶ�
		AddMovementInput(PlayerLocationWithRobotZ - RobotLocation, 1.f, true);
	}
	else
	{
		IsMoveing = false;
	}
}


#pragma endregion