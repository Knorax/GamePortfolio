// Fill out your copyright notice in the Description page of Project Settings.

#include "GamePortfolio/Snake3D/TailSplineManager.h"
#include "Engine/StaticMeshActor.h"
#include "Components/SplineComponent.h"

// Sets default values for this component's properties
UTailSplineManager::UTailSplineManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	InitTailSpline();
}

// Called when the game starts
void UTailSplineManager::BeginPlay()
{
	Super::BeginPlay();

	//OldHeadLocation = GetComponentLocation();

	for (uint32 i = 0; i < InitialTailMeshesCount; i++)
	{
		FVector _SplinePoint = GetComponentLocation() + GetForwardVector() * (InitialTailMeshesCount - i - 1) * -DistanceBetweenTailMeshes;
		TailSpline->AddSplineLocalPoint(_SplinePoint);

		UStaticMeshComponent* _NewTailMesh = SpawnStaticMeshActor(_SplinePoint);
		if (_NewTailMesh)
		{
			TailMeshes.Add(_NewTailMesh);
			TailsDistanceFromHead.Add((InitialTailMeshesCount - i - 1) * DistanceBetweenTailMeshes);

			UE_LOG(LogTemp, Warning, TEXT("TM#%d -- X : %f"),
				i,
				(InitialTailMeshesCount - i - 1) * -DistanceBetweenTailMeshes);
		}
	}
}

// Called every frame
void UTailSplineManager::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (TailMeshes.Num() == 0)
		return;

	FVector _SplinePoint = GetComponentLocation();
	TailSpline->AddSplinePointAtIndex(_SplinePoint, TailSpline->GetNumberOfSplinePoints() - 1, ESplineCoordinateSpace::World);
	TailSpline->RemoveSplinePoint(TailSpline->GetNumberOfSplinePoints() - 1);

	MoveTailMesh(DeltaTime, TailMeshes[TailMeshes.Num() - 1], _SplinePoint);

	float _SplineLenght = TailSpline->GetSplineLength();
	//UE_LOG(LogTemp, Warning, TEXT("TM HEAD -- X : %f, Y : %f, Z : %f -- Spline Lenght : %f"),
	//	_SplinePoint.X,
	//	_SplinePoint.Y,
	//	_SplinePoint.Z,
	//	_SplineLenght);

	for (int32 i = 0; i < TailMeshes.Num() - 1; i++)
	{
		FVector _NewMeshLocation = TailSpline->GetLocationAtDistanceAlongSpline(_SplineLenght - TailsDistanceFromHead[i], ESplineCoordinateSpace::World);

		FVector _dist = TailSpline->GetLocationAtDistanceAlongSpline(_SplineLenght - TailsDistanceFromHead[i], ESplineCoordinateSpace::World);
		//UE_LOG(LogTemp, Warning, TEXT("TM#%d -- X : %f, Y : %f, Z : %f -- Dist : %f"),
		//	i,
		//	_dist.X,
		//	_dist.Y,
		//	_dist.Z,
		//	_SplineLenght - TailsDistanceFromHead[i]);

		TailSpline->AddSplinePointAtIndex(_NewMeshLocation, i, ESplineCoordinateSpace::World);
		TailSpline->RemoveSplinePoint(i + 1);

		MoveTailMesh(DeltaTime, TailMeshes[i], _NewMeshLocation);
	}

	//MoveTailMesh(TailMeshes[0], OldHeadLocation);

	//OldHeadLocation = GetComponentLocation();
}

void UTailSplineManager::InitTailSpline()
{
	TailSpline = CreateDefaultSubobject<USplineComponent>(TEXT("Tail Spline"));
	//TailSpline->SetupAttachment(this);
	TailSpline->ClearSplinePoints();
	//TailSpline->SetWorldLocation(GetComponentLocation());
	TailSpline->ReparamStepsPerSegment = 50;
}

/// <summary>
/// Spawn a mesh at a given location
/// </summary>
/// <param name="InLocation"></param>
/// <returns>New mesh component pointer, null otherwise</returns>
UStaticMeshComponent* UTailSplineManager::SpawnStaticMeshActor(const FVector& InLocation)
{
	AStaticMeshActor* MyNewActor = GetWorld()->SpawnActor<AStaticMeshActor>(AStaticMeshActor::StaticClass());
	MyNewActor->SetMobility(EComponentMobility::Movable);
	MyNewActor->SetActorLocation(InLocation);
	UStaticMeshComponent* MeshComponent = MyNewActor->GetStaticMeshComponent();
	if (MeshComponent)
	{
		MeshComponent->SetStaticMesh(TailMesh);
	}

	return MeshComponent;
}

void UTailSplineManager::MoveTailMesh(float DeltaTime, UStaticMeshComponent* _TailMesh, const FVector& InLocation)
{
	_TailMesh->SetWorldLocation(InLocation);
	//_TailMesh->SetWorldLocation(FMath::VInterpTo(_TailMesh->GetComponentLocation(), InLocation, DeltaTime, 30.0f));
}