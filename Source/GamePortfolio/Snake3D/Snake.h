// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Snake.generated.h"

class UCapsuleComponent;
class UStaticMeshComponent;
class UTailSplineManager;

UCLASS()
class GAMEPORTFOLIO_API ASnake : public APawn
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Components")
		UCapsuleComponent* Capsule;

	UPROPERTY(EditAnywhere, Category = "Components")
		UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = "Components")
		UTailSplineManager* Tail;

	UPROPERTY(EditAnywhere, Category = "Controls")
		float MovementSpeed = 200.0f;

	UPROPERTY(EditAnywhere, Category = "Controls")
		float TurnSpeed = 100.0f;

public:
	// Sets default values for this pawn's properties
	ASnake();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveUp(float Value);
	void MoveRight(float Value);

private:

	/// <summary>
	/// Rotate Actor only when CurrentValue is different from OldValue
	/// </summary>
	/// <param name="CurrentValue">Current float Value</param>
	/// <param name="OldValue">Old float value (will be overriten when value changes)</param>
	/// <param name="Rotation">Rotation wanted upon value changed</param>
	void RotateOnValueChange(const float CurrentValue, float& OutOldValue, const FRotator Rotation);
};
