// Fill out your copyright notice in the Description page of Project Settings.

#include "MeleeEnemy.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Engine/TargetPoint.h"
#include "../../Components/PunchComponent.h"
#include "../IA/Melee/MeleeAIController.h"
#include "../../Player/PlayerCharacter.h"

AMeleeEnemy::AMeleeEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	mDistanceToAttack = 150.0f;
	mPawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	mPawnSensingComponent->SetPeripheralVisionAngle(45);
	mPawnSensingComponent->OnSeePawn.AddDynamic(this, &AMeleeEnemy::OnSeePawn);
}

void AMeleeEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UBehaviorTree * AMeleeEnemy::GetEnemyBehavior() const
{
	return mEnemyBehavior;
}

TArray<ATargetPoint*> AMeleeEnemy::getTargetPoints() const
{
	return TargetPoints;
}

void AMeleeEnemy::SetEnemyBehavior(UBehaviorTree * const enemyBehavior)
{
	mEnemyBehavior = enemyBehavior;
}

void AMeleeEnemy::SetCurrentTargetPoint(int const targetpoint)
{
	currentTargetPoint = targetpoint;
}

float AMeleeEnemy::GetDistanceToAttack() const
{
	return mDistanceToAttack;
}


void AMeleeEnemy::SetDistanceToAttack(const float DistanceToAttack)
{
	mDistanceToAttack = DistanceToAttack;
}


int AMeleeEnemy::GetCurrentTargetPoint()
{
	return currentTargetPoint;
}

void AMeleeEnemy::OnSeePawn(APawn *OtherPawn)
{
	AMeleeAIController * controller = Cast<AMeleeAIController>(GetController());
	if (controller) {
		APlayerCharacter * player = Cast<APlayerCharacter>(OtherPawn);
		if (player) {
			controller->setPlayerCaught(OtherPawn);
		}
	}
}
