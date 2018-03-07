// Fill out your copyright notice in the Description page of Project Settings.

#include "DeathFloor.h"
#include "../Characters/BaseThirdPersonCharacter.h"
#include "../Characters/Components/LifeComponent.h"

// Sets default values
ADeathFloor::ADeathFloor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Body->SetupAttachment(RootComponent);

	EnterCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("EnterCollision"));
	EnterCollision->OnComponentBeginOverlap.AddDynamic(this, &ADeathFloor::OnOverlapBegin);
	EnterCollision->SetupAttachment(Body);
}

// Called when the game starts or when spawned
void ADeathFloor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADeathFloor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADeathFloor::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ABaseThirdPersonCharacter * player = Cast<ABaseThirdPersonCharacter>(OtherActor);
		if (player) {
			ULifeComponent* lifeComponent = player->FindComponentByClass<ULifeComponent>();
			if(lifeComponent)
				lifeComponent->DamageTaken(1000, FVector::ZeroVector);
		}
	}
}

