// Fill out your copyright notice in the Description page of Project Settings.

#include "PoisonTrap.h"
#include "../../../Characters/Player/PlayerCharacter.h"


APoisonTrap::APoisonTrap()
{
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &APoisonTrap::OnOverlapBegin);
}
void APoisonTrap::Tick(float DeltaTime)
{
}

void APoisonTrap::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		APlayerCharacter * chara = Cast<APlayerCharacter>(OtherActor);
		if (chara) {
			chara->GetPoisoned(mTimeDoingDamage,mDamage);
			Destroy();
		}
	}
}




