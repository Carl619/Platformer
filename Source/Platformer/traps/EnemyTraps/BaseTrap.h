// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseTrap.generated.h"

class UBoxComponent;
UCLASS()
class PLATFORMER_API ABaseTrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABaseTrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void CheckLife(float Time);

protected:
	UPROPERTY(EditAnywhere, Category = "Trap")
		UStaticMeshComponent * Body;
	UPROPERTY(EditAnywhere, Category = "Trap")
		UBoxComponent * BoxCollision;
	UPROPERTY(EditAnywhere, Category = "Trap")
	float mLifeTime;
	UPROPERTY(EditAnywhere, Category = "Trap")
	float mCurrentTime;
	UPROPERTY(EditAnywhere, Category = "Trap")
		float mDamage;
	UPROPERTY(EditAnywhere, Category = "Trap")
		float mTimeDoingDamage;
};
