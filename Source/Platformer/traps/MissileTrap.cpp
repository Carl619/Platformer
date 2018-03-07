// Fill out your copyright notice in the Description page of Project Settings.

#include "MissileTrap.h"
#include "../Characters/BaseThirdPersonCharacter.h"
#include "../Characters/Components/LifeComponent.h"
#include "../Bullets/Bullet.h"

// Sets default values
AMissileTrap::AMissileTrap()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Body = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	RootComponent = Body;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AMissileTrap::OnOverlapBegin);
	SphereCollision->SetupAttachment(Body);

	mProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));

}

// Called when the game starts or when spawned
void AMissileTrap::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMissileTrap::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMissileTrap::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ABaseThirdPersonCharacter * chara = Cast<ABaseThirdPersonCharacter>(OtherActor);
		if (chara) {
			ULifeComponent*   lifeComponent = chara->FindComponentByClass<ULifeComponent>();
			if (lifeComponent)
			{
				lifeComponent->DamageTaken(Damage, FVector::ZeroVector);
				Destroy();
			}
			}

		}
		else {}
				ABullet * bull = Cast<ABullet>(OtherActor);
			if (bull) {
				bull->Destroy();
				Destroy();
			}
			else {
				Destroy();
			}
}

void AMissileTrap::HomingMissile(AActor * target)
{
	ABaseThirdPersonCharacter * chara = Cast<ABaseThirdPersonCharacter>(target);
	if (chara) {
		mProjectileMovement->HomingTargetComponent = chara->GetMesh();
		mProjectileMovement->bIsHomingProjectile = true;
		mProjectileMovement->InitialSpeed = InitialSpeed;
		mProjectileMovement->HomingAccelerationMagnitude = HomingAccelerationMagnitude;
	}
}

