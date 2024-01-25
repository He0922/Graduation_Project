// Fill out your copyright notice in the Description page of Project Settings.

#include "ScanObject/C_CanScanObjects_Text.h"
#include "Graduation_Project/DebugHelper.h"


#include "Components/BoxComponent.h"




AC_CanScanObjects_Text::AC_CanScanObjects_Text()
{
	this->Tags.Add(FName("ScanText"));

	BoxCollision_C = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision_C"));
	BoxCollision_C->SetBoxExtent(FVector(100.f, 100.f, 50.f));
	BoxCollision_C->SetupAttachment(GetRootComponent());

	// 设置是否生成碰撞事件(需要使用SetGenerateOverlapEvents来设置是否启用碰撞事件)
	BoxCollision_C->SetGenerateOverlapEvents(true);

	// 设置碰撞响应类型为Overlap
	BoxCollision_C->SetCollisionResponseToAllChannels(ECR_Overlap);

	// 绑定碰撞开始的事件函数
	BoxCollision_C->OnComponentBeginOverlap.AddDynamic(this, &AC_CanScanObjects_Text::OnOverlapBegin);

	// 绑定碰撞结束的事件函数
	BoxCollision_C->OnComponentEndOverlap.AddDynamic(this, &AC_CanScanObjects_Text::OnOverlapEnd);

	
}

void AC_CanScanObjects_Text::BeginPlay()
{
}

void AC_CanScanObjects_Text::Tick(float DeltaTime)
{
}

void AC_CanScanObjects_Text::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void AC_CanScanObjects_Text::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}
