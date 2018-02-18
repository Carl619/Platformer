// Fill out your copyright notice in the Description page of Project Settings.
#include "MeleeAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "../../Melee/MeleeEnemy.h"
#include "Engine/TargetPoint.h"





AMeleeAIController::AMeleeAIController()
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

void AMeleeAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	AMeleeEnemy* melee = Cast<AMeleeEnemy>(InPawn);

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

<<<<<<< HEAD
=======
		CanAttackKeyID = BlackBoardComponent->GetKeyID("LocationToGo");
		BlackBoardComponent->SetValue<UBlackboardKeyType_Object>(LocationToGoKeyID, false);

>>>>>>> origin/master
		// Initialise BehaviorComponent.
		BehaviorComponent->StartTree(*melee->GetEnemyBehavior());
	}
}

// Called every frame
void AMeleeAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AMeleeAIController::setPlayerCaught(APawn * pawn)
{
	if (BlackBoardComponent) {
		BlackBoardComponent->SetValueAsObject(TargetKeyID, pawn);
	}
}

