// Fill out your copyright notice in the Description page of Project Settings.

#include "SlowDownTrap.h"
#include "../../../Characters/Player/PlayerCharacter.h"


ASlowDownTrap::ASlowDownTrap()
{
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &ASlowDownTrap::OnOverlapBegin);
}
void ASlowDownTrap::Tick(float DeltaTime)
{
}

void ASlowDownTrap::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		APlayerCharacter * chara = Cast<APlayerCharacter>(OtherActor);
		if (chara) {
			chara->slowed(mTimeDoingDamage);
			Destroy();
		}
	}
}
