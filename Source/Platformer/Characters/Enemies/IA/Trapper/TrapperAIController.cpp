// Fill out your copyright notice in the Description page of Project Settings.

#include "TrapperAIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "../../Trapper/TrapperEnemy.h"
#include "Engine/TargetPoint.h"





ATrapperAIController::ATrapperAIController()
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

void ATrapperAIController::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	ATrapperEnemy* melee = Cast<ATrapperEnemy>(InPawn);

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

		CanTrapKeyID = BlackBoardComponent->GetKeyID("CanTrap");
		BlackBoardComponent->SetValue<UBlackboardKeyType_Object>(CanTrapKeyID, false);

		// Initialise BehaviorComponent.
		BehaviorComponent->StartTree(*melee->GetEnemyBehavior());
	}
}

// Called every frame
void ATrapperAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ATrapperAIController::setPlayerCaught(APawn * pawn)
{
	if (BlackBoardComponent) {
		BlackBoardComponent->SetValueAsObject(TargetKeyID, pawn);
	}
}





