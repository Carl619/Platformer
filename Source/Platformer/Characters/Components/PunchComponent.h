// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/SphereComponent.h"
#include "Components/ArrowComponent.h"
#include "PunchComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLATFORMER_API UPunchComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPunchComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION()
		void attack();

	UFUNCTION()
		void OnOverlapBeginRightHandCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		void OnOverlapBeginLeftHandCollision(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
		FVector punchDirection();
	UFUNCTION()
		void Punch();
	UFUNCTION()
		void StopPunch();
	/******************************
	***			Getters			***
	*******************************/
	UFUNCTION()
		float getDamage();

	UFUNCTION(BlueprintCallable)
		bool getisPunching();
	UFUNCTION(BlueprintCallable)
		USphereComponent * getLeftHandCollision();
	UFUNCTION(BlueprintCallable)
		USphereComponent * getRightHandCollision();
	/******************************
	***			Setters			***
	*******************************/
	UFUNCTION(BlueprintCallable)
		void setIsPunching(bool punching);

		
private:
	UPROPERTY(EditAnywhere, Category = "DamageSystem")
		USphereComponent * LeftHandCollision;
	UPROPERTY(EditAnywhere, Category = "DamageSystem")
		USphereComponent * RightHandCollision;
	/*THe damage the punch will make*/
	UPROPERTY(EditAnywhere, Category = "DamageSystem")
		float Damage = 20;
	/*The direction the attacked actor will move*/
	UPROPERTY(EditAnywhere, Category = "DamageSystem")
		UArrowComponent* DamageImpulseDirection;
	UPROPERTY(EditAnywhere, Category = "DamageSystem")
		bool isPunching = false;
	UPROPERTY(EditAnywhere, Category = "DamageSystem")
		float waitForNextPunch = 0;
	UPROPERTY(EditAnywhere, Category = "DamageSystem")
		bool canPunch = true;
	UPROPERTY(EditAnywhere, Category = "DamageSystem")
		float currentWaitForNextPunch = 0;
};
