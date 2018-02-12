// Fill out your copyright notice in the Description page of Project Settings.

#include "PunchComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../BaseThirdPersonCharacter.h"
#include "LifeComponent.h"


// Sets default values for this component's properties
UPunchComponent::UPunchComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	LeftHandCollision = CreateDefaultSubobject<USphereComponent>(TEXT("LeftHandCollision"));
	LeftHandCollision->OnComponentBeginOverlap.AddDynamic(this, &UPunchComponent::OnOverlapBeginLeftHandCollision);

	RightHandCollision = CreateDefaultSubobject<USphereComponent>(TEXT("RightHandCollision"));
	RightHandCollision->OnComponentBeginOverlap.AddDynamic(this, &UPunchComponent::OnOverlapBeginRightHandCollision);

	DamageImpulseDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("DamageImpulseDirection"));
	// ...
}


// Called when the game starts
void UPunchComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UPunchComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	if(waitForNextPunch>0){
		if (canPunch == false) {
			currentWaitForNextPunch += DeltaTime;
			if (currentWaitForNextPunch >= waitForNextPunch) {
				currentWaitForNextPunch = 0;
				canPunch = true;
			}
		}
	}
	else {
		if (canPunch == false) {
			canPunch = true;
		}
	}
}

void UPunchComponent::attack()
{
}

void UPunchComponent::OnOverlapBeginRightHandCollision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != GetOwner()) && (OtherComp != nullptr))
	{
		if (canPunch) {
			ABaseThirdPersonCharacter * thirdchara = Cast<ABaseThirdPersonCharacter>(OtherActor);
			if (thirdchara) {
				TArray<ULifeComponent*> Comps;
				thirdchara->GetComponents(Comps);
				if (Comps.Num() > 0)
				{
					Comps[0]->DamageTaken(Damage, DamageImpulseDirection->GetForwardVector());
				}
			}
			canPunch = false;
		}
	}
}

void UPunchComponent::OnOverlapBeginLeftHandCollision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != GetOwner()) && (OtherComp != nullptr))
	{
		if (canPunch) {
			ABaseThirdPersonCharacter * thirdchara = Cast<ABaseThirdPersonCharacter>(OtherActor);
			if (thirdchara) {
				TArray<ULifeComponent*> Comps;
				thirdchara->GetComponents(Comps);
				if (Comps.Num() > 0)
				{
					Comps[0]->DamageTaken(Damage, DamageImpulseDirection->GetForwardVector());
				}
			}
			canPunch = false;
		}
	}
}

FVector UPunchComponent::punchDirection()
{
	return DamageImpulseDirection->GetForwardVector();
}

float UPunchComponent::getDamage()
{
	return Damage;
}


bool UPunchComponent::getisPunching()
{
	return isPunching;
}

void UPunchComponent::setIsPunching(bool punching)
{
	isPunching = punching;
}

void UPunchComponent::Punch()
{
	if (isPunching == false) {
		isPunching = true;
		RightHandCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		LeftHandCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

void UPunchComponent::StopPunch()
{
	if (isPunching == true) {
		isPunching = false;
		RightHandCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		LeftHandCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
}

USphereComponent * UPunchComponent::getLeftHandCollision()
{
	return LeftHandCollision;
}

USphereComponent * UPunchComponent::getRightHandCollision()
{
	return RightHandCollision;
}

