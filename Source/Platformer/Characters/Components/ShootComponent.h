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


	UFUNCTION()
		void SetSpeed(float newSpeed);
	UFUNCTION()
		void Shoot();
	UFUNCTION(BlueprintCallable)
		UArrowComponent* getDirection();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Shoot")
		TSubclassOf<ABullet> ClassType;

	void SetCoolDown(float const CoolDown);
	float GetCoolDown() const;
	void SetCurrentCoolDown(float const CoolDown);
	float GetCurrentCoolDown() const;

private:
	UPROPERTY(EditAnywhere, Category = "Shoot")
		float Speed = 100;
	UPROPERTY(EditAnywhere, Category = "Shoot")
		UArrowComponent* Direction;
	UPROPERTY(EditAnywhere, Category = "Shoot")
		float LocationSpawn = 10.f;
	FRotator SpawnRotation;
	FVector SpawnLocation;

	UPROPERTY(EditAnywhere, Category = "Shoot")
		float mCoolDown;
	UPROPERTY(EditAnywhere, Category = "Shoot")
		float mCurrentCoolDown;
	UPROPERTY(EditAnywhere, Category = "Shoot")
		bool mJustShoot;
	
};
