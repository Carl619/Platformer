// Fill out your copyright notice in the Description page of Project Settings.

#include "Fuel.h"
#include "../Characters/Player/PlayerCharacter.h"

// Sets default values
AFuel::AFuel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Body->SetupAttachment(RootComponent);
	MeshCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	MeshCollision->OnComponentBeginOverlap.AddDynamic(this, &AFuel::OnOverlapBegin);
	MeshCollision->SetupAttachment(Body);
}

void AFuel::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		APlayerCharacter * player = Cast<APlayerCharacter>(OtherActor);
		if (player) {
			player->addFuel(fuel);
			Destroy();
		}
	}
}

// Called when the game starts or when spawned
void AFuel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFuel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

