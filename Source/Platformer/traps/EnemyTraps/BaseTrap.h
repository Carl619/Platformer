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
	/*Checks te remaining time the trap can be actived*/
	UFUNCTION()
		void CheckLife(float Time);

protected:
	UPROPERTY(EditAnywhere, Category = "Trap")
		UStaticMeshComponent * Body;
	UPROPERTY(EditAnywhere, Category = "Trap")
		UBoxComponent * BoxCollision;
	/*time the trap exists*/
	UPROPERTY(EditAnywhere, Category = "Trap")
	float mLifeTime;
	/*current time the trap is existing*/
	UPROPERTY(EditAnywhere, Category = "Trap")
	float mCurrentTime;
	/*the damage the trap can give*/
	UPROPERTY(EditAnywhere, Category = "Trap")
		float mDamage;
	/*the time the trap deals damage*/
	UPROPERTY(EditAnywhere, Category = "Trap")
		float mTimeDoingDamage;
};
