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

	// �����Ƿ�������ײ�¼�(��Ҫʹ��SetGenerateOverlapEvents�������Ƿ�������ײ�¼�)
	BoxCollision_C->SetGenerateOverlapEvents(true);

	// ������ײ��Ӧ����ΪOverlap
	BoxCollision_C->SetCollisionResponseToAllChannels(ECR_Overlap);

	// ����ײ��ʼ���¼�����
	BoxCollision_C->OnComponentBeginOverlap.AddDynamic(this, &AC_CanScanObjects_Text::OnOverlapBegin);

	// ����ײ�������¼�����
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
