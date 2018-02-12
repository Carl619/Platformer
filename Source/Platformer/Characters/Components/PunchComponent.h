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
		float getDamage();

	UFUNCTION(BlueprintCallable)
		bool getisPunching();

	UFUNCTION(BlueprintCallable)
		void setIsPunching(bool punching);
	UFUNCTION()
		void Punch();
	UFUNCTION()
		void StopPunch();
	UFUNCTION(BlueprintCallable)
		USphereComponent * getLeftHandCollision();
	UFUNCTION(BlueprintCallable)
		USphereComponent * getRightHandCollision();


		
private:
	UPROPERTY(EditAnywhere, Category = "DamageSystem")
		USphereComponent * LeftHandCollision;

	UPROPERTY(EditAnywhere, Category = "DamageSystem")
		USphereComponent * RightHandCollision;

	UPROPERTY(EditAnywhere, Category = "DamageSystem")
		float Damage = 20;
	UPROPERTY(EditAnywhere, Category = "DamageSystem")
		UArrowComponent* DamageImpulseDirection;
	UPROPERTY(EditAnywhere, Category = "DamageSystem")
		bool isPunching = false;
	UPROPERTY(EditAnywhere, Category = "DamageSystem")
		float waitForNextPunch = 0;
	UPROPERTY(EditAnywhere, Category = "DamageSystem")
		bool canPunch = true;
		float currentWaitForNextPunch = 0;
};
