// Fill out your copyright notice in the Description page of Project Settings.

#include "ShootComponent.h"
#include "../../Bullets/Bullet.h"


// Sets default values for this component's properties
UShootComponent::UShootComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	Direction = CreateDefaultSubobject<UArrowComponent>(TEXT("ShootDirecion"));
	// ...
}


// Called when the game starts
void UShootComponent::BeginPlay()
{
	Super::BeginPlay();
	SpawnRotation = FRotator(0, 0, 0);
	// ...

	
}


// Called every frame
void UShootComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	SpawnLocation = GetOwner()->GetActorLocation() + Direction->GetForwardVector() * LocationSpawn;
	// ...
}

void UShootComponent::SetSpeed(float newSpeed)
{
	Speed = newSpeed;
}

void UShootComponent::Shoot()
{
	
	ABullet* bullet = (ABullet*)GetWorld()->SpawnActor(ClassType, &SpawnLocation, &SpawnRotation);
	if (bullet) {
		bullet->SetCharaOwner(GetOwner());
		bullet->SetDirection(Direction->GetForwardVector());
		bullet->SetSpeed(Speed);
	}
}

UArrowComponent * UShootComponent::getDirection()
{
	return Direction;
}
