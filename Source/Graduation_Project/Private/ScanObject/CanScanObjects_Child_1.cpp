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
	// �����Ƿ�������ײ�¼�(��Ҫʹ��SetGenerateOverlapEvents�������Ƿ�������ײ�¼�)
	BoxCollision->SetGenerateOverlapEvents(true);

	// ������ײ��Ӧ����ΪOverlap
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Overlap);

	// ����ײ��ʼ���¼�����
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ACanScanObjects_Child_1::OnOverlapBegin);

	// ����ײ�������¼�����
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




