// Fill out your copyright notice in the Description page of Project Settings.

#include "PunchComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "../BaseThirdPersonCharacter.h"
#include "../Enemies/Shooter/ShooterEnemy.h"
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
	RightHandCollision->SetCollisionProfileName(FName("Custom"));
	LeftHandCollision->SetCollisionProfileName(FName("Custom"));
	RightHandCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	LeftHandCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RightHandCollision->SetCollisionObjectType(ECollisionChannel::ECC_Destructible);
	LeftHandCollision->SetCollisionObjectType(ECollisionChannel::ECC_Destructible);
	RightHandCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	LeftHandCollision->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	RightHandCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
	LeftHandCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_WorldStatic, ECollisionResponse::ECR_Overlap);
	RightHandCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	LeftHandCollision->SetCollisionResponseToChannel(ECollisionChannel::ECC_Pawn, ECollisionResponse::ECR_Overlap);
	RightHandCollision->SetSphereRadius(32);
	LeftHandCollision->SetSphereRadius(32);
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
	/*If the owner have to wait for another punch he will wait*/
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
		/*if the punch is activated the collision will see if the character is a third person character and if it is posiible receive damage and a direction*/
		if (canPunch) {
			AShooterEnemy * shooter = Cast<AShooterEnemy>(GetOwner());
			if (!shooter) {
				ABaseThirdPersonCharacter * thirdchara = Cast<ABaseThirdPersonCharacter>(OtherActor);
				if (thirdchara) {
					ULifeComponent* lifeComponent = thirdchara->FindComponentByClass<ULifeComponent>();
					if (lifeComponent)
					{
						lifeComponent->DamageTaken(Damage, DamageImpulseDirection->GetForwardVector());
					}
				}
				canPunch = false;
			}
		}
	}
}

void UPunchComponent::OnOverlapBeginLeftHandCollision(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != GetOwner()) && (OtherComp != nullptr))
	{
		/*if the punch is activated the collision will see if the character is a third person character and if it is posiible receive damage and a direction*/
		if (canPunch) {
			AShooterEnemy * shooter = Cast<AShooterEnemy>(GetOwner());
			if (!shooter) {
				ABaseThirdPersonCharacter * thirdchara = Cast<ABaseThirdPersonCharacter>(OtherActor);
				if (thirdchara) {
					ULifeComponent* lifeComponent = thirdchara->FindComponentByClass<ULifeComponent>();
					if (lifeComponent)
					{
						lifeComponent->DamageTaken(Damage, DamageImpulseDirection->GetForwardVector());
					}
				}
				canPunch = false;
			}
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
	
	/*When the owner is punching the collision of his hands are activated*/
	if (isPunching == false) {
		isPunching = true;
		RightHandCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		LeftHandCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	}
}

void UPunchComponent::StopPunch()
{
	/*When the owner is punching the collision of his hands are activated*/
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

