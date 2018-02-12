// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Characters/Enemies/IA/EnemyAIController.h"
#include "MeleeAIController.generated.h"

class ATargetPoint;
/**
 * 
 */
UCLASS()
class PLATFORMER_API AMeleeAIController : public AEnemyAIController
{
	GENERATED_BODY()
public:
		AMeleeAIController();
	/**
	*   Takes control of the APawn passed.
	*       @params(APawn*) - pawn to control.
	*/
	virtual void Possess(APawn* InPawn) override;
	virtual void Tick(float DeltaTime) override;

	void setPlayerCaught(APawn* pawn);

	/** Blackboard Activated key.*/
	uint8 ActivatedKeyID;
	/** Blackboard target key.*/
	FName TargetKeyID;
	/** Blackboard Attack key.*/
	uint8 AttackKeyID;
	/** Blackboard CanAttack key.*/
	uint8 CanAttackKeyID;
	/** Blackboard LocationToGo key.*/
	FName LocationToGoKeyID;

	int CurrentTargetPoint=0;
private:
	/** Blackboard component.*/
	UPROPERTY(transient)
		class UBlackboardComponent* BlackBoardComponent;
	/** Behavior tree component.*/
	UPROPERTY(transient)
		class UBehaviorTreeComponent* BehaviorComponent;
	UPROPERTY(EditAnywhere)
		TArray<ATargetPoint*> TargetPoints;
	
	
};
