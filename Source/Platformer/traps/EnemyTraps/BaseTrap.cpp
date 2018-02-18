// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseTrap.h"
#include "Components/BoxComponent.h"

// Sets default values
ABaseTrap::ABaseTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = Body;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetupAttachment(Body);
}

// Called when the game starts or when spawned
void ABaseTrap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	mCurrentTime += DeltaTime;
	if (mCurrentTime > mLifeTime)
		Destroy();
}

void ABaseTrap::CheckLife(float Time)
{
	mCurrentTime += Time;
	if (mCurrentTime > mLifeTime)
		Destroy();
}

