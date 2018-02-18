// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/BaseThirdPersonCharacter.h"
#include "Perception/PawnSensingComponent.h"
#include "TrapperEnemy.generated.h"

class UBehaviorTree;
class ATargetPoint;
class ABaseTrap;
class UTrapComponent;
/**
 * 
 */
UCLASS()
class PLATFORMER_API ATrapperEnemy : public ABaseThirdPersonCharacter
{
	GENERATED_BODY()
	

public:
	// Sets default values for this character's properties
	ATrapperEnemy();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UBehaviorTree* GetEnemyBehavior() const;

	TArray<ATargetPoint*> getTargetPoints() const;

	void SetEnemyBehavior(UBehaviorTree* const enemyBehavior);

	void SetCurrentTargetPoint(int const targetpoint);
	float        GetDistanceToAttack() const;
	void         SetDistanceToAttack(const float DistanceToAttack);
	int GetCurrentTargetPoint();
	void  MakeATrap(const int TargetIndex, const int TrapIndex);
	UFUNCTION()
		void OnSeePawn(APawn *OtherPawn);
private:
	/** Behavior tree. */
	UPROPERTY(EditAnywhere, Category = "Platformer|IA")
		UBehaviorTree*           mEnemyBehavior;
	UPROPERTY(EditAnywhere, Category = "Platformer|Traps")
		UTrapComponent*           mTrapComponent;
	
	UPROPERTY(EditAnywhere, Category = "Platformer|IA")
		UPawnSensingComponent*           mPawnSensingComponent;
	UPROPERTY(EditAnywhere, Category = "Platformer|Traps")
		TArray<ATargetPoint*> TargetPoints;
	UPROPERTY(EditAnywhere, Category = "Platformer|Scout")
		int currentTargetPoint;
	/** Max distance to do an effective attack. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platformer|Attack", Meta = (AllowPrivateAccess = true), meta = (DisplayName = "DistanceToAttack"))
		float                    mDistanceToAttack;
	UPROPERTY(EditAnywhere, Category = "Platformer|Traps")
		float mCoolDown;
	UPROPERTY(EditAnywhere, Category = "Platformer|Traps")
		float mCurrentCoolDown;
	UPROPERTY(EditAnywhere, Category = "Platformer|Traps")
		ABaseTrap* TrapDeployed = nullptr;
};
