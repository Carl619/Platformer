// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "traps/EnemyTraps/BaseTrap.h"
#include "SlowDownTrap.generated.h"

/**
 * 
 */
UCLASS()
class PLATFORMER_API ASlowDownTrap : public ABaseTrap
{
	GENERATED_BODY()
	
	
public:
	ASlowDownTrap();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

};
