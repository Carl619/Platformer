// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TrapComponent.generated.h"

class ABaseTrap;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class PLATFORMER_API UTrapComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTrapComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	UFUNCTION()
		TArray<TSubclassOf<ABaseTrap>> GetTrapType();
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
		TArray<TSubclassOf<ABaseTrap>> TrapType;
	ABaseTrap* MakeATrap(int index, FVector TargetLocation);
private:
	FRotator SpawnRotation;
	
};
