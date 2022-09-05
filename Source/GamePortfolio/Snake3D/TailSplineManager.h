// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/SceneComponent.h"
#include "TailSplineManager.generated.h"

class UStaticMesh;
class USplineComponent;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class GAMEPORTFOLIO_API UTailSplineManager : public USceneComponent
{
	GENERATED_BODY()

private:

	TArray<UStaticMeshComponent*> TailMeshes;
	TArray<float> TailsDistanceFromHead;

	FVector OldHeadLocation;

	UPROPERTY(EditAnywhere, Category = "Tail")
		UStaticMesh* TailMesh;

	UPROPERTY(EditAnywhere, Category = "Tail")
		uint32 InitialTailMeshesCount = 3;

	UPROPERTY(EditAnywhere, Category = "Tail")
		float DistanceBetweenTailMeshes = 300.0f;

	UPROPERTY(VisibleAnywhere, Category = "Tail")
		USplineComponent* TailSpline;
public:
	// Sets default values for this component's properties
	UTailSplineManager();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:
	void InitTailSpline();
	UStaticMeshComponent* SpawnStaticMeshActor(const FVector& InLocation);
	void MoveTailMesh(float DeltaTime, UStaticMeshComponent* _TailMesh, const FVector& InLocation);
};
