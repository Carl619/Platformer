// Fill out your copyright notice in the Description page of Project Settings.

#include "PikeTrap.h"
#include "../Characters/BaseThirdPersonCharacter.h"
#include "../Characters/Components/LifeComponent.h"


// Sets default values
APikeTrap::APikeTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = Body;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &APikeTrap::OnOverlapBegin);
	BoxCollision->SetupAttachment(Body);
}

// Called when the game starts or when spawned
void APikeTrap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APikeTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APikeTrap::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ABaseThirdPersonCharacter * chara = Cast<ABaseThirdPersonCharacter>(OtherActor);
		if (chara) {
			TArray<ULifeComponent*> Comps;
			chara->GetComponents(Comps);
			if (Comps.Num() > 0)
			{
				Comps[0]->DamageTaken(Damage, FVector::ZeroVector);
			}
		}
	}
}

