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

	// 在Debug命名空间中添加一个新的函数，用于打印TArray<FHitResult>内容
	static void PrintArrayHitResult(const TArray<FHitResult>& HitResults, const FColor& Color = FColor::Black, int32 InKey = -1)
	{
		// 遍历HitResults数组
		for (const FHitResult& Hit : HitResults)
		{
			// 获取Actor的名称
			FString ActorName = Hit.GetActor()->GetName();
			// 获取碰撞的位置
			FVector Location = Hit.ImpactPoint;
			// 获取碰撞的法线
			FVector Normal = Hit.ImpactNormal;
			// 生成一个消息，包含这些信息
			FString Msg = FString::Printf(TEXT("Hit %s at (%.2f, %.2f, %.2f) with normal (%.2f, %.2f, %.2f)"), *ActorName, Location.X, Location.Y, Location.Z, Normal.X, Normal.Y, Normal.Z);
			// 使用Debug::Print函数打印消息，随机颜色
			Debug::Print(Msg, Color, InKey);
		}
	}

}