// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Portal.generated.h"

UCLASS()
class PLATFORMER_API APortal : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APortal();


	UPROPERTY(EditAnywhere)
		UStaticMeshComponent * Body;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		UBoxComponent* getExitCollision();

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);


	/*The collsion box that when an actor collides, it will be propelled*/
	UPROPERTY(EditAnywhere)
		UBoxComponent* EnterCollision;
	/*The collision box for making an impulse in the actor to make it float*/
	UPROPERTY(EditAnywhere)
		UBoxComponent* ExitCollision;
	/*portal connected to this one and be teleported*/
	UPROPERTY(EditAnywhere)
	APortal* connectedPortal;
	
};
