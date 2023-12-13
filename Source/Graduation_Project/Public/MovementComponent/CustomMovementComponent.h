// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CustomMovementComponent.generated.h"

/**
 * 
 */
UCLASS()
class GRADUATION_PROJECT_API UCustomMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
#pragma region ClimbTrace
public:
	TArray<FHitResult> DoCapsuleTraceMulitByObject(const FVector& Start, const FVector& End, bool showDebugShape); 
	FHitResult DoLineTraceSingleByObject(const FVector& Start, const FVector& End, bool showDebugShape);
#pragma endregion


#pragma region ClimbCore
	void TraceClimbableSurfaces();

	void TraceFromEyeHeight(float TraceDistance, float TraceStartOffset = 0.f);
#pragma endregion


#pragma region ClimbVariables
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement: Climbing", meta = (AllowPrivateAccess = "true"))
	TArray<TEnumAsByte<EObjectTypeQuery> > ClimbableSurfaceTraceTypes;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement: Climbing", meta = (AllowPrivateAccess = "true"))
	float ClimbCapsuleTraceRadius = 50.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Character Movement: Climbing", meta = (AllowPrivateAccess = "true"))
	float ClimbCapsuleTraceHalfHeight = 72.f;
#pragma endregion


};
