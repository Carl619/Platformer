// Fill out your copyright notice in the Description page of Project Settings.

#include "TreasureBlock.h"
#include "../Characters/Components/LifeComponent.h"


// Sets default values
ATreasureBlock::ATreasureBlock()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Body->SetupAttachment(RootComponent);

}

void ATreasureBlock::reward(APlayerCharacter * player)
{
	ULifeComponent*   lifeComponent;
	if (!rewarded) {
		switch (objectType)
		{
		case 0:
			player->addCollectible(1);
			break;
		case 1:
			player->addFuel(100);
			break;
		case 2:
			lifeComponent = player->FindComponentByClass<ULifeComponent>();
			if (lifeComponent)
			{
				lifeComponent->heal(10);
			}
			break;
		case 3:
			player->addAmmo(10);
		case 4:
			lifeComponent = player->FindComponentByClass<ULifeComponent>();
			if (lifeComponent)
			{
				lifeComponent->becomeImmune();
			}
			break;
		default:
			break;
		}
		rewarded = true;
		Body->SetMaterial(0,MaterialUsed);
	}
}

// Called when the game starts or when spawned
void ATreasureBlock::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATreasureBlock::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (canrestart) {
		if (rewarded) {
			remainingtime -= DeltaTime;
			if (remainingtime < 0) {
				remainingtime = rechargetime;
				rewarded = false;
				Body->SetMaterial(0,MaterialNormal);
			}
		}
	}
}

