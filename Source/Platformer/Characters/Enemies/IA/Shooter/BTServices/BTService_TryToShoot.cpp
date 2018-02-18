// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_TryToShoot.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "../ShooterAIController.h"
#include "../../../../Player/PlayerCharacter.h"
#include "../../../Shooter/ShooterEnemy.h"
#include "../../../../Components/PunchComponent.h"
#include "../../../../Components/ShootComponent.h"




UBTService_TryToShoot::UBTService_TryToShoot()
{
	bCreateNodeInstance = true;
}

void UBTService_TryToShoot::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// Get the AMeleeAIController.
	AShooterAIController* enemyController = Cast<AShooterAIController>(OwnerComp.GetAIOwner());
	// Get the player.
	APlayerCharacter*       player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

 	if (IsValid(enemyController) && IsValid(player))
	{
		// Get the enemy character.
		AShooterEnemy* controlledPawn = Cast<AShooterEnemy>(enemyController->GetPawn());

		if (IsValid(controlledPawn))
		{
			float distance = controlledPawn->GetDistanceTo(player);

			if (distance <= controlledPawn->GetDistanceToShoot())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsBool("CanShoot", true);
			}
			else
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsBool("CanShoot", false);
			}
		}
	}
}

