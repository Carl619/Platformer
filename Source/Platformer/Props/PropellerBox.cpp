// Fill out your copyright notice in the Description page of Project Settings.

#include "PropellerBox.h"
#include "../Characters/Player/PlayerCharacter.h"


// Sets default values
APropellerBox::APropellerBox()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Body->SetupAttachment(RootComponent);

	EnterCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("EnterCollision"));
	EnterCollision->OnComponentBeginOverlap.AddDynamic(this, &APropellerBox::OnOverlapBegin);
	EnterCollision->SetupAttachment(Body);
	
	ImpulseDirection = CreateDefaultSubobject<UArrowComponent>(TEXT("ImpulseDirection"));
	ImpulseDirection->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void APropellerBox::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APropellerBox::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APropellerBox::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{

	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		APlayerCharacter * player = Cast<APlayerCharacter>(OtherActor);
		if (player) {
			FVector impulseVector = ImpulseDirection->GetForwardVector();
			impulseVector *= impulse;
			player->LaunchCharacter(impulseVector, false, true);
		}
	}
}

