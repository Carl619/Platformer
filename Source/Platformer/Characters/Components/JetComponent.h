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

	void setForceZget(float force);
	void setJetFuel(float fuel);
	UFUNCTION(BlueprintCallable)
		float getMaxFuel();
	UFUNCTION(BlueprintCallable)
	float getFuel();
	void setFuelLost(float fuel);
	void addFuel(float FuelAmmount);
	bool getPropelling();
	void setPropelling(bool pro);


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
