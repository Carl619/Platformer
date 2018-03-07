// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "MissileTrap.generated.h"

UCLASS()
class PLATFORMER_API AMissileTrap : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMissileTrap();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	/*The missile chases the player*/
	UFUNCTION()
		void HomingMissile(AActor * target);

private:
	UPROPERTY(EditAnywhere)
		UStaticMeshComponent * Body;
	UPROPERTY(EditAnywhere)
		USphereComponent * SphereCollision;
	UPROPERTY(EditAnywhere)
		UProjectileMovementComponent * mProjectileMovement;
	UPROPERTY(EditAnywhere, Category = "Platformer|Damage")
		float Damage = 10;
	UPROPERTY(EditAnywhere, Category = "Platformer|Homing")
		float InitialSpeed = 1000;
	UPROPERTY(EditAnywhere, Category = "Platformer|Homing")
		float HomingAccelerationMagnitude = 4500;
	
};
