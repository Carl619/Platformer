// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "../Characters/Player/PlayerCharacter.h"
#include "TreasureBlock.generated.h"

UCLASS()
class PLATFORMER_API ATreasureBlock : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATreasureBlock();


	UPROPERTY(EditAnywhere)
		UStaticMeshComponent * Body;

	UFUNCTION()
		void reward(APlayerCharacter * player);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	/*material use when it hasn't been activated*/
	UPROPERTY(EditAnywhere, Category = "Platformer|Material")
	UMaterialInterface * MaterialNormal;
	/*material when the reward is activated*/
	UPROPERTY(EditAnywhere, Category = "Platformer|Material")
	UMaterialInterface * MaterialUsed;
	/*if the block has given the reward*/
	UPROPERTY(EditAnywhere, Category = "Platformer|Treasure")
	bool rewarded = false;
	/*if we want to restart the reward*/
	UPROPERTY(EditAnywhere, Category = "Platformer|Treasure")
		bool canrestart = false;
	/*the current time to wait for a reawrd after it is activated*/
	UPROPERTY(EditAnywhere, Category = "Platformer|Treasure")
		float remainingtime = 0;
	/*Time to charge the reward*/
	UPROPERTY(EditAnywhere, Category = "Platformer|Treasure")
		float rechargetime = 0;
	/*Reward gicen, 0 a coin, 1 fuel, 2 life, 3 ammo, 4 immune*/
	UPROPERTY(EditAnywhere, Category = "Platformer|Treasure")
	int objectType = 0;
	
};
