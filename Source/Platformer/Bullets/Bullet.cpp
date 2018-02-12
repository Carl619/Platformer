// Fill out your copyright notice in the Description page of Project Settings.

#include "Bullet.h"
#include "../Characters/BaseThirdPersonCharacter.h"
#include "../Characters/Components/LifeComponent.h"

// Sets default values
ABullet::ABullet()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = Body;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlapBegin);
	SphereCollision->SetupAttachment(Body);
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FVector newLocation = Direction * (Speed * DeltaTime);
	newLocation += GetActorLocation();
	SetActorLocation(newLocation);
}


void ABullet::SetSpeed(float newSpeed)
{
	Speed = newSpeed;
}

void ABullet::SetDirection(FVector newDirection)
{
	Direction = newDirection;
}

void ABullet::SetCharaOwner(AActor * newOwner)
{
	ABaseThirdPersonCharacter * chara = Cast<ABaseThirdPersonCharacter>(newOwner);
	if(chara)
		OwnerCharacter = chara;
}

void ABullet::SetDamage(float dam)
{
	Damage = dam;
}

void ABullet::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ABaseThirdPersonCharacter * chara = Cast<ABaseThirdPersonCharacter>(OtherActor);
		if (chara) {
			/*I have to make sure the bullet doesn't damage the creater ofthe bullet, because it can make the bullet ot be destroyed at the begining*/
			if (chara != OwnerCharacter) {
				TArray<ULifeComponent*> Comps;
				chara->GetComponents(Comps);
				if (Comps.Num() > 0)
				{
					Comps[0]->DamageTaken(Damage, FVector::ZeroVector);
					Destroy();
				}
			}

		}
		else {
			/*Bullets don't destroy between them*/
			ABullet * bull = Cast<ABullet>(OtherActor);
			if (bull) {

			}
			else {
				/*Anything else destroy the bullet*/
				Destroy();
			}
		}
	}

	
}

