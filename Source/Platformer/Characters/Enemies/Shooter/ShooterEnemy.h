// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseThirdPersonCharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "ShooterEnemy.generated.h"


class UBehaviorTree;
class ATargetPoint;
class UShootComponent;

/**
 * 
 */
UCLASS()
class PLATFORMER_API AShooterEnemy : public ABaseThirdPersonCharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AShooterEnemy();
		// Called every frame
		virtual void Tick(float DeltaTime) override;

	UBehaviorTree* GetEnemyBehavior() const;

	TArray<ATargetPoint*> getTargetPoints() const;

	void SetEnemyBehavior(UBehaviorTree* const enemyBehavior);

	void SetCurrentTargetPoint(int const targetpoint);
	float        GetDistanceToAttack() const;
	void         SetDistanceToAttack(const float DistanceToAttack);
	int GetCurrentTargetPoint();
	void SetDistanceToShoot(float const tooNearToShoot);
	float GetDistanceToShoot() const;
	UFUNCTION()
		void OnSeePawn(APawn *OtherPawn);
	
	UFUNCTION(BlueprintCallable)
		UShootComponent* getShoot();
private:
	/** Behavior tree. */
	UPROPERTY(EditAnywhere, Category = "Platformer|IA")
		UBehaviorTree*           mEnemyBehavior;
	/*Sensing component to detect the player*/
	UPROPERTY(EditAnywhere, Category = "Platformer|IA")
		UPawnSensingComponent*           mPawnSensingComponent;
	/*points to scout*/
	UPROPERTY(EditAnywhere, Category = "Platformer|Scout")
		TArray<ATargetPoint*> TargetPoints;
	/*Current target point to go*/
	UPROPERTY(EditAnywhere, Category = "Platformer|Scout")
		int currentTargetPoint;
	/** Max distance to do an effective punch. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platformer|Attack", Meta = (AllowPrivateAccess = true), meta = (DisplayName = "DistanceToAttack"))
		float                    mDistanceToAttack;
	/** Max distance to do an effective shoot. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platformer|Attack", Meta = (AllowPrivateAccess = true), meta = (DisplayName = "TooNearToShoot"))
		float                    mDistanceToShoot;
	/*shoot component*/
	UPROPERTY(EditAnywhere, Category = "Platformer|Shoot")
		UShootComponent*mShoot;
};
