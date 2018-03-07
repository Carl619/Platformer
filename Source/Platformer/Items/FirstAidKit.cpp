// Fill out your copyright notice in the Description page of Project Settings.

#include "FirstAidKit.h"
#include "../Characters/Player/PlayerCharacter.h"
#include "../Characters/Components/LifeComponent.h"

// Sets default values
AFirstAidKit::AFirstAidKit()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Body->SetupAttachment(RootComponent);
	MeshCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	MeshCollision->OnComponentBeginOverlap.AddDynamic(this, &AFirstAidKit::OnOverlapBegin);
	MeshCollision->SetupAttachment(Body);
}

// Called when the game starts or when spawned
void AFirstAidKit::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFirstAidKit::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFirstAidKit::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ABaseThirdPersonCharacter * chara = Cast<ABaseThirdPersonCharacter>(OtherActor);
		if (chara) {
			ULifeComponent*   lifeComponent = chara->FindComponentByClass<ULifeComponent>();
			if (lifeComponent)
			{
				lifeComponent->heal(life);
				Destroy();
			}
			}
	}
}

