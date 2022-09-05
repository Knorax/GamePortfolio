// Fill out your copyright notice in the Description page of Project Settings.


#include "GamePortfolio/Snake3D/SnakePlayer.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"


ASnakePlayer::ASnakePlayer()
{
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm Component"));
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera Component"));

	SpringArm->SetupAttachment(RootComponent);
	Camera->SetupAttachment(SpringArm);
}

// Called when the game starts or when spawned
void ASnakePlayer::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ASnakePlayer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ASnakePlayer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveUp"), this, &ASnakePlayer::MoveUp);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &ASnakePlayer::MoveRight);
}
