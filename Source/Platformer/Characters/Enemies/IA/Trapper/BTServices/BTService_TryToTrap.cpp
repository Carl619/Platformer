// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_TryToTrap.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "../TrapperAIController.h"
#include "../../../../Player/PlayerCharacter.h"
#include "../../../Trapper/TrapperEnemy.h"
#include "../../../../Components/TrapComponent.h"




UBTService_TryToTrap::UBTService_TryToTrap()
{
	bCreateNodeInstance = true;
}

void UBTService_TryToTrap::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// Get the AMeleeAIController.
	ATrapperAIController* enemyController = Cast<ATrapperAIController>(OwnerComp.GetAIOwner());
	// Get the player.
	APlayerCharacter*       player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (IsValid(enemyController) && IsValid(player))
	{
		// Get the enemy character.
		ATrapperEnemy* controlledPawn = Cast<ATrapperEnemy>(enemyController->GetPawn());

		if (IsValid(controlledPawn))
		{
			float distance = controlledPawn->GetDistanceTo(player);

			if (distance <= controlledPawn->GetDistanceToAttack())
			{
				OwnerComp.GetBlackboardComponent()->SetValueAsBool("CanTrap", true);
			}
		}
	}
}





