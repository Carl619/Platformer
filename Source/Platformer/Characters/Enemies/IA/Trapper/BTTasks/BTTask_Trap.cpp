// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Trap.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "../TrapperAIController.h"
#include "../../../../Player/PlayerCharacter.h"
#include "../../../Trapper/TrapperEnemy.h"
#include "../../../../Components/LifeComponent.h"
#include "../../../../Components/PunchComponent.h"
#include "../../../../Components/TrapComponent.h"
#include "../../../../../traps/EnemyTraps/BaseTrap.h"

EBTNodeResult::Type UBTTask_Trap::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	// Get the ATrapperAIController.
	ATrapperAIController* enemyController = Cast<ATrapperAIController>(OwnerComp.GetAIOwner());
	// Get the player.
	APlayerCharacter*       player = Cast<APlayerCharacter>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(enemyController->TargetKeyID));

	if (IsValid(enemyController) && IsValid(player))
	{
		// Get the enemy character.
		ATrapperEnemy* controlledPawn = Cast<ATrapperEnemy>(enemyController->GetPawn());

		if (IsValid(controlledPawn))
		{
			/*checks if player is near enough to start deploying traps*/
			float             distance = controlledPawn->GetDistanceTo(player);
				if (distance <= controlledPawn->GetDistanceToAttack())
				{
					if (controlledPawn->getTargetPoints().Num() > 0) {
						UTrapComponent* damageComponent = enemyController->GetPawn()->FindComponentByClass<UTrapComponent>();
						/*choose a random trap and a random location to put it*/
						int selectedLoc = FMath::RandRange(0, controlledPawn->getTargetPoints().Num() - 1);
						int selectedTrap = FMath::RandRange(0, damageComponent->GetTrapType().Num() - 1);
						controlledPawn->MakeATrap(selectedLoc,selectedTrap);
					}
				}
				return EBTNodeResult::Succeeded;
		}
	}
	return EBTNodeResult::Failed;
}




