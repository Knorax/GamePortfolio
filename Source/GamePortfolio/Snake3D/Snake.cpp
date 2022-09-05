// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePortfolio/Snake3D/Snake.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GamePortfolio/Snake3D/TailSplineManager.h"

// Sets default values
ASnake::ASnake()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Capsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	Tail = CreateDefaultSubobject<UTailSplineManager>(TEXT("Tail Scene Component"));

	RootComponent = Capsule;
	Mesh->SetupAttachment(Capsule);
	Tail->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void ASnake::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASnake::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector TargetLocation = GetActorLocation() + DeltaTime * MovementSpeed * GetActorForwardVector();

	this->SetActorLocation(TargetLocation);
}

void ASnake::MoveUp(float Value)
{
	static float OldValue = 0.0f;
	//RotateOnValueChange(Value, OldValue, FRotator(FMath::RoundHalfFromZero(Value) * 90, 0, 0));
	AddActorLocalRotation(FRotator(Value * TurnSpeed * UGameplayStatics::GetWorldDeltaSeconds(this), 0.0f, 0.0f));
}

void ASnake::MoveRight(float Value)
{
	static float OldValue = 0.0f;

	//RotateOnValueChange(Value, OldValue, FRotator(0, FMath::RoundHalfFromZero(Value) * 90, 0));
	AddActorLocalRotation(FRotator(0, Value * TurnSpeed * UGameplayStatics::GetWorldDeltaSeconds(this), 0));
}

void ASnake::RotateOnValueChange(const float CurrentValue, float& OutOldValue, const FRotator Rotation)
{
	if (!FMath::IsNearlyEqual(CurrentValue, OutOldValue))
	{
		UE_LOG(LogTemp, Warning, TEXT("MoveUP Value = %f"), FMath::RoundHalfFromZero(CurrentValue));
		AddActorLocalRotation(Rotation);
		OutOldValue = CurrentValue;
	}
}