// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "JetComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLATFORMER_API UJetComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UJetComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	/******************************
	***			Setters			***
	*******************************/
	void setForceZget(float force);
	void setJetFuel(float fuel);
	void setFuelLost(float fuel);
	void setPropelling(bool pro);
	/******************************
	***			Getters			***
	*******************************/
		UFUNCTION(BlueprintCallable)
		float getMaxFuel();
	UFUNCTION(BlueprintCallable)
	float getFuel();
	bool getPropelling();
	/*Add more fuel*/
	void addFuel(float FuelAmmount);


private:
	UPROPERTY(EditAnywhere, Category = "Jet")
		float ForceZJet = 100;
	UPROPERTY(EditAnywhere, Category = "Jet")
		float JetFuel = 100;
	UPROPERTY(EditAnywhere, Category = "Jet")
		float MaxJetFuel = 100;
	UPROPERTY(EditAnywhere, Category = "Jet")
		float FuelLost = 1;
	UPROPERTY(EditAnywhere, Category = "Jet")
		bool propelling = false;
	
};
