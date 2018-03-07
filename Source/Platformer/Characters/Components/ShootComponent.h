// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/ArrowComponent.h"
#include "ShootComponent.generated.h"

class ABullet;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLATFORMER_API UShootComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UShootComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	/*Manages tha action of shoot and the craetion of the bullet*/
	UFUNCTION()
		void Shoot();

	/*The class type of the bullet to shoot, used to create actors from blueprint bullets*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
		TSubclassOf<ABullet> ClassType;

	/******************************
	***			Getters			***
	*******************************/
	UFUNCTION(BlueprintCallable)
		UArrowComponent* getDirection();
	float GetCurrentCoolDown() const;
	float GetCoolDown() const;
	/******************************
	***			Setters			***
	*******************************/
	void SetCoolDown(float const CoolDown);
	void SetCurrentCoolDown(float const CoolDown);
	UFUNCTION()
		void SetSpeed(float const newSpeed);

private:
	UPROPERTY(EditAnywhere, Category = "Shoot")
		float Speed = 100;
	UPROPERTY(EditAnywhere, Category = "Shoot")
		UArrowComponent* Direction;
	/*The distance from the arrow direction and how much we want the offset of the spawn of the bullet*/
	UPROPERTY(EditAnywhere, Category = "Shoot")
		float LocationSpawn = 10.f;
	/*Location of the bullet spawned*/
	FRotator SpawnRotation;
	FVector SpawnLocation;
	/*The minimum time between each shoot*/
	UPROPERTY(EditAnywhere, Category = "Shoot")
		float mCoolDown;
	/*The current time to wait*/
	UPROPERTY(EditAnywhere, Category = "Shoot")
		float mCurrentCoolDown;
	/*boolean to know we recently shoot and have to wait for shooting again*/
	UPROPERTY(EditAnywhere, Category = "Shoot")
		bool mJustShoot;
	
};
