// Fill out your copyright notice in the Description page of Project Settings.


#include "ScanObject/CanScanObjects_Child_1.h"
#include "Components/BoxComponent.h"
#include "Graduation_Project/DebugHelper.h"


ACanScanObjects_Child_1::ACanScanObjects_Child_1(const FObjectInitializer& ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	BoxCollision->SetBoxExtent(FVector(100.f, 100.f, 50.f));
	BoxCollision->SetupAttachment(GetRootComponent());
	// 设置是否生成碰撞事件(需要使用SetGenerateOverlapEvents来设置是否启用碰撞事件)
	BoxCollision->SetGenerateOverlapEvents(true);

	// 设置碰撞响应类型为Overlap
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Overlap);

	// 绑定碰撞开始的事件函数
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ACanScanObjects_Child_1::OnOverlapBegin);

	// 绑定碰撞结束的事件函数
	BoxCollision->OnComponentEndOverlap.AddDynamic(this, &ACanScanObjects_Child_1::OnOverlapEnd);
}



void ACanScanObjects_Child_1::BeginPlay()
{
	Super::BeginPlay();
	
}

void ACanScanObjects_Child_1::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ACanScanObjects_Child_1::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Debug::Print("Overlap Begin!");
}

void ACanScanObjects_Child_1::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Debug::Print("Overlap End!");
}




