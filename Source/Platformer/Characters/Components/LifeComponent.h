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


	UFUNCTION()
		void ContinuousDamageTaken(float DamageAttack);

	UFUNCTION()
		void heal(float health);
	/******************************
	***			Getters			***
	*******************************/
	UFUNCTION(BlueprintCallable)
		float getLife();
	UFUNCTION(BlueprintCallable)
		float getMaxLife();
	/******************************
	***			Setters			***
	*******************************/
	UFUNCTION()
		void setLife(float life);
	UFUNCTION()
		void setMaxLife(float life);
	/*This make the owner invulnerable to damage*/
	UFUNCTION()
	void becomeImmune();
	/*This function manages the time the owner is inmune*/
	UFUNCTION()
	void BeingImmune(float DeltaTime);

private:
	/*The current life of the onwer*/
	UPROPERTY(EditAnywhere, Category = "HealthSystem")
		float Life = 100;
	/*Max life of the owner*/
	UPROPERTY(EditAnywhere, Category = "HealthSystem")
		float MaxLife = 100;
	/*THe multiplier of the impulse when the owner receive damage*/
	UPROPERTY(EditAnywhere, Category = "HealthSystem")
		float ImpulseDamageMultiplier = 300;
	/*Inmune time*/
	UPROPERTY(EditAnywhere, Category = "HealthSystem")
		float CurrentImmuneTime = 0;
	/*Max inmune time*/
	UPROPERTY(EditAnywhere, Category = "HealthSystem")
		float ImnuneDuration = 100;
	/*Bool to know if it is inmune*/
	UPROPERTY(EditAnywhere, Category = "HealthSystem")
		bool imnune = false;
	
};
