// Fill out your copyright notice in the Description page of Project Settings.


#include "MovementComponent/CustomMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Explorer.h"



void UCustomMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	TraceClimbableSurfaces();
	TraceFromEyeHeight(100.f);
}



#pragma region ClimbTrace
TArray<FHitResult> UCustomMovementComponent::DoCapsuleTraceMulitByObject(const FVector& Start, const FVector& End, bool showDebugShape)
{
	TArray<FHitResult> OutCapsuleTraceHitResult;

	UKismetSystemLibrary::CapsuleTraceMultiForObjects(
		this,
		Start,
		End,
		ClimbCapsuleTraceRadius,
		ClimbCapsuleTraceHalfHeight,
		ClimbableSurfaceTraceTypes,
		false,
		TArray<AActor*>(),
		showDebugShape ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
		OutCapsuleTraceHitResult,
		false
	);
	return OutCapsuleTraceHitResult;
}


FHitResult UCustomMovementComponent::DoLineTraceSingleByObject(const FVector& Start, const FVector& End, bool showDebugShape)
{
	FHitResult OutLineTraceHitResult;

	UKismetSystemLibrary::LineTraceSingleForObjects(
		this,
		Start,
		End,
		ClimbableSurfaceTraceTypes,
		false,
		TArray<AActor*>(),
		showDebugShape ? EDrawDebugTrace::ForOneFrame : EDrawDebugTrace::None,
		OutLineTraceHitResult,
		false
	);

	return OutLineTraceHitResult;
}
#pragma endregion


#pragma region ClimbCore
void UCustomMovementComponent::TraceClimbableSurfaces()
{
	const FVector StartOffset = UpdatedComponent->GetForwardVector() * 30.f;
	const FVector Start = UpdatedComponent->GetComponentLocation() + StartOffset;
	const FVector End = Start + UpdatedComponent->GetForwardVector();
	
	DoCapsuleTraceMulitByObject(Start,End, true);
}


void UCustomMovementComponent::TraceFromEyeHeight(float TraceDistance, float TraceStartOffset)
{
	const FVector ComponentLocation = UpdatedComponent->GetComponentLocation();
	const FVector EyeHeightOffset = UpdatedComponent->GetUpVector() * (CharacterOwner->BaseEyeHeight + TraceStartOffset);
	
	const FVector Start = ComponentLocation + EyeHeightOffset;
	const FVector End = UpdatedComponent->GetForwardVector() + TraceDistance;

	DoLineTraceSingleByObject(Start, End, true);

}
#pragma endregion