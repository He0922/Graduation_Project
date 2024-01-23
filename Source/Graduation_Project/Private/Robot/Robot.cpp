// Fill out your copyright notice in the Description page of Project Settings.


#include "Robot/Robot.h"
#include "ScanObject/CanScanObjects_Child_1.h"


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

	// ����ͷ�����߼���Ƿ�����Ŀ�� 
	if (Player->Camera_OutLineTraceHitResult.IsValidIndex(0))
	{
		// �����е�λ�ø�ֵ��MoveSpecifyLocation����
		MoveSpecifyLocation = Player->MouseClickLocation;
	}


	if (Player->bRobotFollowPlayer)
	{
		Debug::Print("Robot Follow Player");
		MoveToPlayerLocation();
	}
	else if (Player->bRobotMoveSpecifyLocation && Player->Camera_OutLineTraceHitResult.IsValidIndex(0))
	{
		Debug::Print("Robot MoveSpecifyLocation");
		MoveToSpecifyLocation(MoveSpecifyLocation);
	}
	else if (Player->bRobotScanObjects)
	{
		Debug::Print("Robot ScanObjects");
		RobotScanObjects(Player->ScanObjectsLocation);
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
	if (Player->bRobotFollowPlayer)
	{
		LookAtPlayer();

		// ��ȡRobot����ҵ�λ���Լ�Robot��ǰ������
		const FVector PlayerLocation = Player->GetActorLocation();
		const FVector RobotLocation = this->GetActorLocation();

		// ����Robot��Player֮��ľ���
		float Distance = (PlayerLocation - RobotLocation).Size();

		// ����һ���ݲ�ֵ����ʾRobot��Player֮�����С����
		const float Tolerance = 100.f;

		if (Distance > Move_Threshold + Tolerance)
		{
			// ���㳯�����λ��������ת�Ƕȣ������λ�õ�Z�����滻ΪRobotλ�õ�Z����
			FVector PlayerLocationWithRobotZ = FVector(PlayerLocation.X, PlayerLocation.Y, RobotLocation.Z);
			FRotator FaceToPlayerRotation = UKismetMathLibrary::FindLookAtRotation(RobotLocation, PlayerLocationWithRobotZ);

			// ����Robot����
			this->SetActorRotation(FaceToPlayerRotation);

			// ������ͼ�����һ����λ�������ƶ�Robot������ҷ����ƶ�
			AddMovementInput(PlayerLocationWithRobotZ - RobotLocation, 1.f, true);
		}
	}
}


void ARobot::MoveToSpecifyLocation(const FVector& SpecifyLocation)
{
	// �жϻ������Ƿ��ڸ������
	if(!Player->bRobotFollowPlayer)
	{
		LookAtSpecifyLocation(SpecifyLocation);

		// ��ȡ�����˵�λ��
		const FVector RobotLocation = this->GetActorLocation();

		// ����ָ��λ�úͻ�����֮��ľ���
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

void ARobot::RobotScanObjects(const FVector& ScanLocation)
{
	LookAtSpecifyLocation(ScanLocation);

	FVector RobotLocation = this->GetActorLocation();
	FVector RobotScanObjectsLocation = ScanLocation;

	float Distance = (RobotScanObjectsLocation - RobotLocation).Size();

	const float Threshold = 150.f;

	// ���������뱻ɨ����Ʒ֮������������ƶ�
	if (Distance > Move_Threshold + Threshold)
	{
		FVector ScanObjectsLocation = FVector(RobotScanObjectsLocation.X, RobotScanObjectsLocation.Y, RobotScanObjectsLocation.Z + 100.f);
		FRotator FaceToScanObjectLocation = UKismetMathLibrary::FindLookAtRotation(RobotLocation, ScanObjectsLocation);

		this->SetActorRotation(FaceToScanObjectLocation);

		AddMovementInput(ScanObjectsLocation - RobotLocation, 1.f, true);
	}
}

#pragma endregion


