// Fill out your copyright notice in the Description page of Project Settings.


#include "Task/BTTask_MoveToPlayer.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "NavigationSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Graduation_Project/Public/Explorer.h"

UBTTask_MoveToPlayer::UBTTask_MoveToPlayer()
{
	Player = Cast<AExplorer>(UGameplayStatics::GetActorOfClass(GetWorld(), AExplorer::StaticClass()));

	NodeName = "Move To Player Location";
}

EBTNodeResult::Type UBTTask_MoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* Controller = OwnerComp.GetAIOwner();
	UBlackboardComponent* Blackboard = OwnerComp.GetBlackboardComponent();
	if (!Controller || !Blackboard) return EBTNodeResult::Failed;

	const auto Pawn = Controller->GetPawn();
	if (!Pawn) return EBTNodeResult::Failed;

	const auto NavSystem = UNavigationSystemV1::GetCurrent(Pawn);
	if (!NavSystem) return EBTNodeResult::Failed;


	FNavLocation NavLocation;
	const auto Found = NavSystem->GetRandomReachablePointInRadius(Pawn->GetActorLocation(), Move_To_Target_Raidus, NavLocation);
	if (!Found) return EBTNodeResult::Failed;


	Blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, Player->GetActorLocation());
	return EBTNodeResult::Succeeded;

}
