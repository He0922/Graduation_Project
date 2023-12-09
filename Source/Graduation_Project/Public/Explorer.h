// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "InputActionValue.h"

#include "Explorer.generated.h"

UCLASS()
class GRADUATION_PROJECT_API AExplorer : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AExplorer();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


#pragma region PlayerComponent
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpringArm")
	class USpringArmComponent* SpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "SpringArm")
	class UCameraComponent* Camera;

#pragma endregion



#pragma region PlayerAction
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MappingContext")
	class UInputMappingContext* Action_MappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* Move_Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* Look_Action;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* Jump_Action;

	void Move_Function(const FInputActionValue& Value);
	void Look_Function(const FInputActionValue& Value);
#pragma endregion

};
