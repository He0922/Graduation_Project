// Fill out your copyright notice in the Description page of Project Settings.


#include "Robot/Robot.h"
#include "Graduation_Project/Public/Explorer.h"
#include "Kismet/GameplayStatics.h"
#include "Graduation_Project/DebugHelper.h"
#include "GameFramework/CharacterMovementComponent.h"

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
}

// Called every frame
void ARobot::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ARobot::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


AActor* ARobot::GetPlayer() const
{
	return Player;
}


float ARobot::CheckDistance()
{
	const FVector PlayerLocation = Player->GetActorLocation();
	const FVector RobotLocation = this->GetActorLocation();

	float Distance = (PlayerLocation - RobotLocation).Size();
	
	// Debug::Print(FString::SanitizeFloat(Distance));

	return Distance;
}

bool ARobot::FollowPlayer()
{
	float Distance = CheckDistance();

	if (Distance > 300.f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ARobot::SetRobotSpeed()
{
	float Distance = CheckDistance();
	if (Distance > 600.f) // ����������700.f
	{
		MovementComponent->MaxWalkSpeed = 700.f; // �����ٶ�Ϊ600.f
	}
	else if (500.f < Distance && Distance < 600.f) // ���������400.f��700.f֮��
	{
		MovementComponent->MaxWalkSpeed = 500.f; // �����ٶ�Ϊ400.f
	}
	else if (400.f < Distance && Distance < 500.f) // ���������400.f��700.f֮��
	{
		MovementComponent->MaxWalkSpeed = 400.f; // �����ٶ�Ϊ400.f
	}
	else if (200.f < Distance && Distance < 400.f) // ���������200.f��400.f֮��
	{
		MovementComponent->MaxWalkSpeed = 300.f; // �����ٶ�Ϊ200.f
	}
	else if (100.f < Distance && Distance < 200.f) // ���������200.f��400.f֮��
	{
		MovementComponent->MaxWalkSpeed = 200.f; // �����ٶ�Ϊ200.f
	}

	// Debug::Print(FString::SanitizeFloat(MovementComponent->GetMaxSpeed()));
}
