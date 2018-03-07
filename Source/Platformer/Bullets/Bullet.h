// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Bullet.generated.h"

class ABaseThirdPersonCharacter;
UCLASS()
class PLATFORMER_API ABullet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABullet();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
/******************************
***			Setters			***
*******************************/
	UFUNCTION()
		void SetDirection(FVector newDirection);
	UFUNCTION()
		void SetSpeed(float newSpeed);
	UFUNCTION()
		void SetCharaOwner(AActor* newOwner);
	UFUNCTION()
		void SetDamage(float dam);
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
private:
	UPROPERTY(EditAnywhere, Category = "Platformer|Bullet")
		UStaticMeshComponent * Body;
	/*The Speed the bullet moves*/
	UPROPERTY(EditAnywhere, Category = "Platformer|Bullet")
		float Speed = 100;
	/*THe owner of the bullet to avoid that the bullet overlaps him and damage him*/
	UPROPERTY(EditAnywhere, Category = "Platformer|Bullet")
		ABaseThirdPersonCharacter * OwnerCharacter;
	/*The direction the bullet moves*/
	UPROPERTY(EditAnywhere, Category = "Platformer|Bullet")
		FVector Direction;
	/*The damage the bullet deals*/
	UPROPERTY(EditAnywhere, Category = "Platformer|Bullet")
		float Damage = 10;
	/*Sphere Collision*/
	UPROPERTY(EditAnywhere, Category = "Platformer|Bullet")
		USphereComponent * SphereCollision;
	
};
