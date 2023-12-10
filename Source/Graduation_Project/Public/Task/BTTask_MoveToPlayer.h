// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MoveToPlayer.generated.h"

/**
 * 
 */
UCLASS()
class GRADUATION_PROJECT_API UBTTask_MoveToPlayer : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_MoveToPlayer();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

	class AExplorer* Player;


	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	float Move_To_Target_Raidus = 1000.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "AI")
	FBlackboardKeySelector AimLocationKey;
};
