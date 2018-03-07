// Fill out your copyright notice in the Description page of Project Settings.

#include "SplinePath.h"


// Sets default values
ASplinePath::ASplinePath()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mSplinePath = CreateDefaultSubobject<USplineComponent>(TEXT("Spline"));
	mSplinePath->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ASplinePath::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASplinePath::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (trap) {
		FVector NewPosition = FMath::Lerp<FVector>(mSplinePath->GetLocationAtSplinePoint(0, ESplineCoordinateSpace::World), mSplinePath->GetLocationAtSplinePoint(mSplinePath->GetNumberOfSplinePoints() - 1, ESplineCoordinateSpace::World), path);
		/*When path is near of a extreme I change the orient of the object*/
		if (path > 0.95) {
			pathSide = -1;
		}
		else if (path < 0.05) {
			pathSide = 1;
		}
		path += speed*DeltaTime*pathSide;
		trap->SetActorLocation(NewPosition);
	}
}

