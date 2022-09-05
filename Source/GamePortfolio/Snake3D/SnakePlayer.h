// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GamePortfolio/Snake3D/Snake.h"
#include "SnakePlayer.generated.h"

class USpringArmComponent;
class UCameraComponent;
/**
 *
 */
UCLASS()
class GAMEPORTFOLIO_API ASnakePlayer : public ASnake
{
	GENERATED_BODY()

private:
	UPROPERTY(EditAnywhere, Category = "Components")
		USpringArmComponent* SpringArm;
	UPROPERTY(EditAnywhere, Category = "Components")
		UCameraComponent* Camera;


public:
	ASnakePlayer();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
