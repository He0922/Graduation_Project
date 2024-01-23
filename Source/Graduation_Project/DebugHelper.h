#pragma once
namespace Debug
{
	static void Print(const FString& Msg, const FColor& Color = FColor::Red, int32 InKey = -1)
	{
		// FColor::MakeRandomColor()
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(InKey, 0.0f, Color, Msg);
		}

		UE_LOG(LogTemp, Warning, TEXT("%s"), *Msg);
	}

	// ��Debug�����ռ������һ���µĺ��������ڴ�ӡTArray<FHitResult>����
	static void PrintArrayHitResult(const TArray<FHitResult>& HitResults, const FColor& Color = FColor::Black, int32 InKey = -1)
	{
		// ����HitResults����
		for (const FHitResult& Hit : HitResults)
		{
			// ��ȡActor������
			FString ActorName = Hit.GetActor()->GetName();
			// ��ȡ��ײ��λ��
			FVector Location = Hit.ImpactPoint;
			// ��ȡ��ײ�ķ���
			FVector Normal = Hit.ImpactNormal;
			// ����һ����Ϣ��������Щ��Ϣ
			FString Msg = FString::Printf(TEXT("Hit %s at (%.2f, %.2f, %.2f) with normal (%.2f, %.2f, %.2f)"), *ActorName, Location.X, Location.Y, Location.Z, Normal.X, Normal.Y, Normal.Z);
			// ʹ��Debug::Print������ӡ��Ϣ�������ɫ
			Debug::Print(Msg, Color, InKey);
		}
	}

}