// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"
#include "PropellerBox.generated.h"

UCLASS()
class PLATFORMER_API APropellerBox : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APropellerBox();




/*	UPROPERTY(EditAnywhere)
		UArrowComponent* ImpulseDirection;*/

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent * Body;
	/*The collsion box that when an actor collides, it will be propelled*/
	UPROPERTY(EditAnywhere)
		UBoxComponent* EnterCollision;
	/*direction to be impulsed*/
	UPROPERTY(EditAnywhere)
		UArrowComponent* ImpulseDirection;
	/*imoulse given to player*/
	UPROPERTY(EditAnywhere, Category = "Platformer")
		float impulse = 0;
	
};
