// Fill out your copyright notice in the Description page of Project Settings.

#include "TrapperEnemy.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Engine/TargetPoint.h"
#include "../../Components/PunchComponent.h"
#include "../IA/Trapper/TrapperAIController.h"
#include "../../Components/LifeComponent.h"
#include "../../Components/ShootComponent.h"
#include "../../Player/PlayerCharacter.h"
#include "../../../traps/EnemyTraps/BaseTrap.h"
#include "../../Components/TrapComponent.h"



ATrapperEnemy::ATrapperEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	mDistanceToAttack = 150.0f;
	mPawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	mPawnSensingComponent->SetPeripheralVisionAngle(90);
	mPawnSensingComponent->OnSeePawn.AddDynamic(this, &ATrapperEnemy::OnSeePawn);
	mTrapComponent = CreateDefaultSubobject<UTrapComponent>(TEXT("TrapComponent"));
}

void ATrapperEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	mCurrentCoolDown += DeltaTime;
}

UBehaviorTree * ATrapperEnemy::GetEnemyBehavior() const
{
	return mEnemyBehavior;
}

TArray<ATargetPoint*> ATrapperEnemy::getTargetPoints() const
{
	return TargetPoints;
}

void ATrapperEnemy::SetEnemyBehavior(UBehaviorTree * const enemyBehavior)
{
	mEnemyBehavior = enemyBehavior;
}

void ATrapperEnemy::SetCurrentTargetPoint(int const targetpoint)
{
	currentTargetPoint = targetpoint;
}

float ATrapperEnemy::GetDistanceToAttack() const
{
	return mDistanceToAttack;
}


void ATrapperEnemy::SetDistanceToAttack(const float DistanceToAttack)
{
	mDistanceToAttack = DistanceToAttack;
}


int ATrapperEnemy::GetCurrentTargetPoint()
{
	return currentTargetPoint;
}

void ATrapperEnemy::MakeATrap(const int TargetIndex, const int TrapIndex)
{
	if (TrapDeployed == nullptr) {
		if (mCurrentCoolDown > mCoolDown) {
			TrapDeployed = mTrapComponent->MakeATrap(TrapIndex, TargetPoints[TargetIndex]->GetActorLocation());
			mCurrentCoolDown = 0;
		}
	}
}


void ATrapperEnemy::OnSeePawn(APawn *OtherPawn)
{
	ATrapperAIController * controller = Cast<ATrapperAIController>(GetController());
	if (controller) {
		APlayerCharacter * player = Cast<APlayerCharacter>(OtherPawn);
		if (player) {
			controller->setPlayerCaught(OtherPawn);
		}
	}
}





