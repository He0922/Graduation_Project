// Fill out your copyright notice in the Description page of Project Settings.


#include "Explorer.h"
#include "Robot/Robot.h"

#include "Kismet/GameplayStatics.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Graduation_Project/DebugHelper.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "MovementComponent/CustomMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "CollisionQueryParams.h"

#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"


// Sets default values
AExplorer::AExplorer(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer.SetDefaultSubobjectClass<UCustomMovementComponent>(ACharacter::CharacterMovementComponentName))
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CustomMovementComponent = Cast<UCustomMovementComponent>(GetCharacterMovement());

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 600.f;
	SpringArm->bUsePawnControlRotation = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
	Camera->bUsePawnControlRotation = false;



}

// Called when the game starts or when spawned
void AExplorer::BeginPlay()
{
	Super::BeginPlay();

	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(Action_MappingContext, 0);
		}
	}
	
	Robot = Cast<ARobot>(UGameplayStatics::GetActorOfClass(GetWorld(), ARobot::StaticClass()));
}

// Called every frame
void AExplorer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	CameraTrace_Start_End();
	Debug::Print(FString::Printf(TEXT("Bool value: %s"), bRobotFollowPlayer ? TEXT("true") : TEXT("false")));
}

// Called to bind functionality to input
void AExplorer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* MyEnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		MyEnhancedInput->BindAction(Move_Action, ETriggerEvent::Triggered, this, &AExplorer::Move_Function);
		MyEnhancedInput->BindAction(Look_Action, ETriggerEvent::Triggered, this, &AExplorer::Look_Function);
		MyEnhancedInput->BindAction(Jump_Action, ETriggerEvent::Triggered, this, &ACharacter::Jump);
		MyEnhancedInput->BindAction(Jump_Action, ETriggerEvent::Completed, this, &ACharacter::StopJumping);
		MyEnhancedInput->BindAction(ControlRobotMove, ETriggerEvent::Started, this, &AExplorer::Control_RobotMove);
		MyEnhancedInput->BindAction(RobotScanTarget_Action, ETriggerEvent::Started, this, &AExplorer::RobotScanTarget);
		MyEnhancedInput->BindAction(RobotFollowPlayer_Action, ETriggerEvent::Started, this, &AExplorer::RobotFollowPlayer);
	}

}

void AExplorer::Move_Function(const FInputActionValue& Value)
{
	const FVector2D MoveVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		const FRotator Rotation = Controller->GetControlRotation();
		const FRotator YawRotation(0.f, Rotation.Yaw, 0.f);

		const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

		AddMovementInput(ForwardDirection, MoveVector.Y);
		AddMovementInput(RightDirection, MoveVector.X);
	}

}

// 玩家鼠标控制摄像机视角的旋转
void AExplorer::Look_Function(const FInputActionValue& Value)
{
	const FVector2D MouseVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		AddControllerPitchInput(MouseVector.Y);
		AddControllerYawInput(MouseVector.X);
	}
}


// 机器人移动到鼠标指定位置
void AExplorer::Control_RobotMove(const FInputActionValue& Value)
{
	if (!bRobotFollowPlayer)
	{
		if (Camera_OutLineTraceHitResult.IsValidIndex(0))
		{
			RobotMoveToSpecifyLocation = true;
			MouseClickLocation = Camera_OutLineTraceHitResult[0].Location;
		}
	}
	
}

// 机器人扫描地形的行动
void AExplorer::RobotScanTarget(const FInputActionValue& Value)
{
}

// 判断机器人是跟随人物移动还是移动到鼠标指定位置
void AExplorer::RobotFollowPlayer(const FInputActionValue& Value)
{
	if (bRobotFollowPlayer) { bRobotFollowPlayer = false; }
	else { bRobotFollowPlayer = true; }
}



#pragma region Camera
void AExplorer::CameraTrace(const FVector& Start, const FVector& End)
{
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	ECollisionChannel TraceChannel = ECC_Visibility;

	FCollisionQueryParams TraceParams(TEXT("CameraTrace"),false);
	TraceParams.AddIgnoredActors(ActorsToIgnore);
	

	DrawDebugLine(GetWorld(), Start, End, FColor::Red, false, 0.f, 0, 1.f);
	bCameraTraceHit = GetWorld()->LineTraceMultiByChannel(Camera_OutLineTraceHitResult, Start, End, TraceChannel, TraceParams);

	Debug::PrintArrayHitResult(Camera_OutLineTraceHitResult);

}

void AExplorer::CameraTrace_Start_End()
{
	float CameraTraceLeght = 2000.f;

	const FVector CameraLocation = Camera->GetComponentLocation();
	const FVector CameraForward = Camera->GetForwardVector();
	const FVector CameraRight = Camera->GetRightVector();

	const FVector Start = CameraLocation + CameraForward + CameraRight * 20.f;
	const FVector End = Start + CameraForward * CameraTraceLeght;

	CameraTrace(Start, End);
}

#pragma endregion