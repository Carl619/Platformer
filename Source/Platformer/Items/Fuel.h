// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Fuel.generated.h"

UCLASS()
class PLATFORMER_API AFuel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFuel();


	UPROPERTY(EditAnywhere)
		USphereComponent * MeshCollision;

	UPROPERTY(EditAnywhere)
		UStaticMeshComponent * Body;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);



protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditAnywhere, Category = "Platformer")
		float rotationSpeed = 100;
	UPROPERTY(EditAnywhere, Category = "Platformer")
		float fuel = 100;


	
};
