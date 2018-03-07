// Fill out your copyright notice in the Description page of Project Settings.

#include "ShootComponent.h"
#include "../../Bullets/Bullet.h"


// Sets default values for this component's properties
UShootComponent::UShootComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	Direction = CreateDefaultSubobject<UArrowComponent>(TEXT("ShootDirecion"));
	mCurrentCoolDown = 0;
	mJustShoot = false;
	// ...
}


// Called when the game starts
void UShootComponent::BeginPlay()
{
	Super::BeginPlay();
	SpawnRotation = FRotator(0, 0, 0);
	// ...

	
}


// Called every frame
void UShootComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	SpawnLocation = GetOwner()->GetActorLocation() + Direction->GetForwardVector() * LocationSpawn;
	/*If he just shoot each tick will update the cool down to wait for the next shoot*/
	if (mJustShoot) {
		mCurrentCoolDown += DeltaTime;
		if (mCurrentCoolDown > mCoolDown) {
			mJustShoot = false;
			mCurrentCoolDown = 0;
		}
	}

	// ...
}

void UShootComponent::SetSpeed(float const newSpeed)
{
	Speed = newSpeed;
}

void UShootComponent::Shoot()
{
	/*If the owner have to wait for each shoot the boolean mJustShoot will decide if the onwer can shoot*/
	if (!mJustShoot) {
		/*There is a possibility that the bullet that is created is inmiedately destroyed because the target is too near so the bullet is destroyed at the moment of creation and the shooter thinks it wasn't created*/
		ABullet* bullet = (ABullet*)GetWorld()->SpawnActor(ClassType, &SpawnLocation, &SpawnRotation);
				mJustShoot = true;
				mCurrentCoolDown = 0;	
				if (bullet) {
				/*creation of the bullet*/
				bullet->SetCharaOwner(GetOwner());
				bullet->SetDirection(Direction->GetForwardVector());
				bullet->SetSpeed(Speed);
			}

	}
}

UArrowComponent * UShootComponent::getDirection()
{
	return Direction;
}


void UShootComponent::SetCoolDown(float const CoolDown)
{
	mCoolDown = CoolDown;
}

float UShootComponent::GetCoolDown() const
{
	return mCoolDown;
}

void UShootComponent::SetCurrentCoolDown(float const CoolDown)
{
	mCurrentCoolDown = CoolDown;
}

float UShootComponent::GetCurrentCoolDown() const
{
	return mCurrentCoolDown;
}

