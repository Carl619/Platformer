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

	UPROPERTY(EditAnywhere, Category = "Platformer|Material")
	UMaterialInterface * MaterialNormal;
	UPROPERTY(EditAnywhere, Category = "Platformer|Material")
	UMaterialInterface * MaterialUsed;
	UPROPERTY(EditAnywhere, Category = "Platformer|Treasure")
	bool rewarded = false;
	UPROPERTY(EditAnywhere, Category = "Platformer|Treasure")
		bool canrestart = false;
	UPROPERTY(EditAnywhere, Category = "Platformer|Treasure")
		float remainingtime = 0;
	UPROPERTY(EditAnywhere, Category = "Platformer|Treasure")
		float rechargetime = 0;
	UPROPERTY(EditAnywhere, Category = "Platformer|Treasure")
	int objectType = 0;
	
};
