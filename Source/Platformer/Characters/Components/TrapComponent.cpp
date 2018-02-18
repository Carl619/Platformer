// Fill out your copyright notice in the Description page of Project Settings.

#include "TrapComponent.h"
#include "../../traps/EnemyTraps/BaseTrap.h"
#include "../../traps/EnemyTraps/ExplosiveTrap/ExplosiveTrap.h"
#include "../../traps/EnemyTraps/PoisonTrap/PoisonTrap.h"
#include "../../traps/EnemyTraps/SlowDownTrap/SlowDownTrap.h"
// Sets default values for this component's properties
UTrapComponent::UTrapComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UTrapComponent::BeginPlay()
{
	Super::BeginPlay();
	SpawnRotation = FRotator(0, 0, 0);
	// ...
	
}

ABaseTrap* UTrapComponent::MakeATrap(int index, FVector TargetLocation)
{
	ABaseTrap* trap = (ABaseTrap*)GetWorld()->SpawnActor(TrapType[index], &TargetLocation, &SpawnRotation);
	return trap;
}


// Called every frame
void UTrapComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

TArray<TSubclassOf<ABaseTrap>> UTrapComponent::GetTrapType()
{
	return TrapType;
}

