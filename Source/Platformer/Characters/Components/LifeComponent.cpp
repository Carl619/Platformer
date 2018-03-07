// Fill out your copyright notice in the Description page of Project Settings.

#include "LifeComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../Player/PlayerCharacter.h"



// Sets default values for this component's properties
ULifeComponent::ULifeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void ULifeComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void ULifeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	APlayerCharacter * player = Cast<APlayerCharacter>(GetOwner());
	if (!player) {
		if (Life <= 0) {
			GetOwner()->Destroy();
		}
	}

	BeingImmune(DeltaTime);
	// ...
}

void ULifeComponent::DamageTaken(float DamageAttack,FVector ImpulseDirection)
{
	if (imnune == false) {
		/*Each attack the owner receives he will be impulsed in the attacker direction, 
		or if there is no direction will be a jump.*/
		Life -= DamageAttack;
		ACharacter * chara = Cast<ACharacter>(GetOwner());
		UCharacterMovementComponent* moveComponent = GetOwner()->FindComponentByClass<UCharacterMovementComponent>();
		if (moveComponent)
		{
			FVector LaunchDirection = ImpulseDirection + FVector(0, 0, 0.5);
			LaunchDirection *= (moveComponent->Mass*ImpulseDamageMultiplier);
			chara->LaunchCharacter(LaunchDirection, true, true);
		}
	}
}



void ULifeComponent::ContinuousDamageTaken(float DamageAttack)
{
	if (imnune == false) {
		Life -= DamageAttack;
	}
}

void ULifeComponent::heal(float health)
{
	Life += health;
	if (Life > MaxLife)
		Life = MaxLife;
}

float ULifeComponent::getLife()
{
	return Life;
}

void ULifeComponent::setLife(float life)
{
	Life = life;
}

float ULifeComponent::getMaxLife()
{
	return MaxLife;
}

void ULifeComponent::setMaxLife(float life)
{
	MaxLife = life;
}

void ULifeComponent::becomeImmune()
{
	imnune = true;
}

void ULifeComponent::BeingImmune(float DeltaTime)
{
	if (imnune) {
		CurrentImmuneTime += DeltaTime;
		if (CurrentImmuneTime >= ImnuneDuration)
			imnune = false;
	}
}

