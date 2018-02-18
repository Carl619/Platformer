// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterEnemy.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "Engine/TargetPoint.h"
#include "../../Components/PunchComponent.h"
#include "../IA/Shooter/ShooterAIController.h"
#include "../../Components/ShootComponent.h"
#include "../../Player/PlayerCharacter.h"



AShooterEnemy::AShooterEnemy()
{
	PrimaryActorTick.bCanEverTick = true;
	mDistanceToAttack = 150.0f;
	mPawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensingComponent"));
	mPawnSensingComponent->SetPeripheralVisionAngle(45);
	mPawnSensingComponent->OnSeePawn.AddDynamic(this, &AShooterEnemy::OnSeePawn);
	mShoot = CreateDefaultSubobject<UShootComponent>(TEXT("ShootComponent"));
	mDistanceToShoot = 500;
}

void AShooterEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UBehaviorTree * AShooterEnemy::GetEnemyBehavior() const
{
	return mEnemyBehavior;
}

TArray<ATargetPoint*> AShooterEnemy::getTargetPoints() const
{
	return TargetPoints;
}

void AShooterEnemy::SetEnemyBehavior(UBehaviorTree * const enemyBehavior)
{
	mEnemyBehavior = enemyBehavior;
}

void AShooterEnemy::SetCurrentTargetPoint(int const targetpoint)
{
	currentTargetPoint = targetpoint;
}

float AShooterEnemy::GetDistanceToAttack() const
{
	return mDistanceToAttack;
}


void AShooterEnemy::SetDistanceToAttack(const float DistanceToAttack)
{
	mDistanceToAttack = DistanceToAttack;
}


int AShooterEnemy::GetCurrentTargetPoint()
{
	return currentTargetPoint;
}

void AShooterEnemy::SetDistanceToShoot(float const tooNearToShoot)
{
	mDistanceToShoot = tooNearToShoot;
}

float AShooterEnemy::GetDistanceToShoot() const
{
	return mDistanceToShoot;
}


void AShooterEnemy::OnSeePawn(APawn *OtherPawn)
{
	AShooterAIController * controller = Cast<AShooterAIController>(GetController());
	if (controller) {
		APlayerCharacter * player = Cast<APlayerCharacter>(OtherPawn);
		if (player) {
			controller->setPlayerCaught(OtherPawn);
		}
	}
}

UShootComponent * AShooterEnemy::getShoot()
{
	return mShoot;
}

