// Fill out your copyright notice in the Description page of Project Settings.

#include "JetComponent.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"



// Sets default values for this component's properties
UJetComponent::UJetComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UJetComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UJetComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/*This bool makes sure that the jet pack only is active when the user wants*/
	if (propelling) {
		TArray<UCharacterMovementComponent*> Comps;

		ACharacter * chara = Cast<ACharacter>(GetOwner());
		chara->GetComponents(Comps);
		if (Comps.Num() > 0)
		{
			/*The jetpack unlike the jumps is used continously*/
			UCharacterMovementComponent* FoundComp = Comps[0];
			FoundComp->AddForce(FVector(0, 0, ForceZJet*FoundComp->Mass));
			JetFuel = JetFuel - FuelLost*DeltaTime;
			if (JetFuel < 0)
				JetFuel = 0;
		}
	}
}

void UJetComponent::setForceZget(float force)
{
	ForceZJet = force;
}

void UJetComponent::setJetFuel(float fuel)
{
	JetFuel = fuel;
}

float UJetComponent::getMaxFuel()
{
	return MaxJetFuel;
}

float UJetComponent::getFuel()
{
	return JetFuel;
}

void UJetComponent::setFuelLost(float fuel)
{
	FuelLost = fuel;
}

void UJetComponent::addFuel(float FuelAmmount)
{
	JetFuel += FuelAmmount;
	if (JetFuel > MaxJetFuel)
		JetFuel = MaxJetFuel;
}

bool UJetComponent::getPropelling()
{
	return propelling;
}

void UJetComponent::setPropelling(bool pro)
{
	propelling = pro;
}

