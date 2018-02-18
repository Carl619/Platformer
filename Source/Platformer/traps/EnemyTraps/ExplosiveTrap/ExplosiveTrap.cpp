// Fill out your copyright notice in the Description page of Project Settings.

#include "ExplosiveTrap.h"
#include "../../../Characters/BaseThirdPersonCharacter.h"
#include "../../../Characters/Components/LifeComponent.h"


AExplosiveTrap::AExplosiveTrap()
{
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AExplosiveTrap::OnOverlapBegin);
}
void AExplosiveTrap::Tick(float DeltaTime)
{
}

void AExplosiveTrap::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr))
	{
		ABaseThirdPersonCharacter * chara = Cast<ABaseThirdPersonCharacter>(OtherActor);
		if (chara) {
			TArray<ULifeComponent*> Comps;
			chara->GetComponents(Comps);
			if (Comps.Num() > 0)
			{
				Comps[0]->DamageTaken(mDamage, FVector::ZeroVector);
				Destroy();
			}
		}
	}
}




