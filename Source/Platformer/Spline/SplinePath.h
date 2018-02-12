// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Components/SplineComponent.h"
#include "SplinePath.generated.h"

UCLASS()
class PLATFORMER_API ASplinePath : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASplinePath();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "Platformer|Spline")
		USplineComponent * mSplinePath;
	/*The object designed for the spline*/
	UPROPERTY(EditAnywhere, Category = "Platformer|Spline")
		AActor * trap;
	/*The speed the object moves in the speed*/
	UPROPERTY(EditAnywhere, Category = "Platformer|Spline")
		float speed;
	/*path is the variable used for lerp using the first and the last spline point*/
	UPROPERTY(EditAnywhere, Category = "Platformer|Spline")
		float path;
	/*pathside is used to set where is oriented the object in the spline*/
	int pathSide = 1;
};
