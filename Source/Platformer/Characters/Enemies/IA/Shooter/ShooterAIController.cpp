// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "../../Shooter/ShooterEnemy.h"
#include "Engine/TargetPoint.h"



AShooterAIController::AShooterAIController()
{
	PrimaryActorTick.bCanEverTick = true;
	// Create a UBlackBoardComponent.
	BlackBoardComponent = CreateDefaultSubobject<UBlackboardComponent>(TEXT("BlackBoardComponent"));
	// Create a UBehaviorTreeComponent.
	BehaviorComponent = CreateDefaultSubobject<UBehaviorTreeComponent>(TEXT("BehaviorComponent"));

	TargetKeyID = "Target";
	LocationToGoKeyID = "LocationToGo";
	CurrentTargetPoint = 0;

}

void AShooterAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	AShooterEnemy* melee = Cast<AShooterEnemy>(InPawn);

	if ((IsValid(melee)) && (IsValid(melee->GetEnemyBehavior())))
	{
		// Initialise BlackBoardComponent.
		BlackBoardComponent->InitializeBlackboard(*melee->GetEnemyBehavior()->BlackboardAsset);

		TargetPoints.Empty();
		for (int i = 0; i < melee->getTargetPoints().Num(); i++) {
			TargetPoints.Add(melee->getTargetPoints()[i]);
		}

		CurrentTargetPoint = melee->GetCurrentTargetPoint();


		ActivatedKeyID = BlackBoardComponent->GetKeyID("Activated");
		BlackBoardComponent->SetValueAsBool("Activated", false);

		AttackKeyID = BlackBoardComponent->GetKeyID("Attack");
		BlackBoardComponent->SetValue<UBlackboardKeyType_Object>(AttackKeyID, false);

		CanAttackKeyID = BlackBoardComponent->GetKeyID("CanAttack");
		BlackBoardComponent->SetValue<UBlackboardKeyType_Object>(CanAttackKeyID, false);

		ShootKeyID = BlackBoardComponent->GetKeyID("Shoot");
		BlackBoardComponent->SetValue<UBlackboardKeyType_Object>(ShootKeyID, false);

		CanShootKeyID = BlackBoardComponent->GetKeyID("CanShoot");
		BlackBoardComponent->SetValue<UBlackboardKeyType_Object>(CanShootKeyID, false);

		// Initialise BehaviorComponent.
		BehaviorComponent->StartTree(*melee->GetEnemyBehavior());
	}
}

// Called every frame
void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShooterAIController::setPlayerCaught(APawn * pawn)
{
	if (BlackBoardComponent) {
		BlackBoardComponent->SetValueAsObject(TargetKeyID, pawn);
	}
}



