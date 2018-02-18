// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LifeComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLATFORMER_API ULifeComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULifeComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
		void DamageTaken(float DamageAttack, FVector ImpulseDirection);

<<<<<<< HEAD
	UFUNCTION()
		void ContinuousDamageTaken(float DamageAttack);
=======

>>>>>>> origin/master
	UFUNCTION()
		void heal(float health);

	UFUNCTION(BlueprintCallable)
		float getLife();
	UFUNCTION()
		void setLife(float life);
	UFUNCTION(BlueprintCallable)
		float getMaxLife();
	UFUNCTION()
		void setMaxLife(float life);
	UFUNCTION()
	void becomeImmune();
	UFUNCTION()
	void BeingImmune(float DeltaTime);

private:
	UPROPERTY(EditAnywhere, Category = "HealthSystem")
		float Life = 100;
	UPROPERTY(EditAnywhere, Category = "HealthSystem")
		float MaxLife = 100;
	UPROPERTY(EditAnywhere, Category = "HealthSystem")
		float ImpulseDamageMultiplier = 300;
	UPROPERTY(EditAnywhere, Category = "HealthSystem")
		float CurrentImmuneTime = 0;
	UPROPERTY(EditAnywhere, Category = "HealthSystem")
		float ImnuneDuration = 100;
	UPROPERTY(EditAnywhere, Category = "HealthSystem")
		bool imnune = false;
	
};
