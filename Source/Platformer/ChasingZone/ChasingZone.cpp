// Fill out your copyright notice in the Description page of Project Settings.

#include "ChasingZone.h"
#include "../Characters/Player/PlayerCharacter.h"

// Sets default values
AChasingZone::AChasingZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	EnterZone = CreateDefaultSubobject<UBoxComponent>(TEXT("EnterZone"));
	EnterZone->OnComponentBeginOverlap.AddDynamic(this, &AChasingZone::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AChasingZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AChasingZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AChasingZone::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		APlayerCharacter * player = Cast<APlayerCharacter>(OtherActor);
		if (player) {
			/*when the players enters warns all the missiles to star attacking*/
			for (int i = 0; i < missiles.Num(); i++) {
				if (missiles[i]->IsValidLowLevel()) {
					missiles[i]->HomingMissile(player);
				}
			}
		}
	}
}

