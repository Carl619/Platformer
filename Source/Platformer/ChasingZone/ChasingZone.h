// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "../traps/MissileTrap.h"
#include "ChasingZone.generated.h"

UCLASS()
class PLATFORMER_API AChasingZone : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AChasingZone();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


private:


	/*The collsion box that when an actor collides, it will be propelled*/
	UPROPERTY(EditAnywhere)
		UBoxComponent* EnterZone;
	UPROPERTY(EditAnywhere)
	TArray<AMissileTrap*> missiles;
	
};
