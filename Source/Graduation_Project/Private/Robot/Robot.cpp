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

	LookAtPlayer();
	MoveToPlayerLocation();

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


