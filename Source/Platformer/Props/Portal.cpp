// Fill out your copyright notice in the Description page of Project Settings.

#include "Portal.h"
#include "../Characters/Player/PlayerCharacter.h"

// Sets default values
APortal::APortal()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Body->SetupAttachment(RootComponent);

	EnterCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("EnterCollision"));
	EnterCollision->OnComponentBeginOverlap.AddDynamic(this, &APortal::OnOverlapBegin);
	EnterCollision->SetupAttachment(Body);

	ExitCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("ExitCollision"));
	ExitCollision->SetupAttachment(Body);
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

UBoxComponent * APortal::getExitCollision()
{
	return ExitCollision;
}

void APortal::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		APlayerCharacter * player = Cast<APlayerCharacter>(OtherActor);
		if (player) {
			player->SetActorLocation(connectedPortal->getExitCollision()->GetComponentLocation());
		}
	}
}

