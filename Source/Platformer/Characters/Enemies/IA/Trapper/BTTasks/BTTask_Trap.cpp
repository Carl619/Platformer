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
	ATrapperAIController* enemyController = Cast<ATrapperAIController>(OwnerComp.GetAIOwner());

	APlayerCharacter*       player = Cast<APlayerCharacter>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(enemyController->TargetKeyID));

	if (IsValid(enemyController) && IsValid(player))
	{

		ATrapperEnemy* controlledPawn = Cast<ATrapperEnemy>(enemyController->GetPawn());

		if (IsValid(controlledPawn))
		{
			float             distance = controlledPawn->GetDistanceTo(player);
				if (distance <= controlledPawn->GetDistanceToAttack())
				{
					if (controlledPawn->getTargetPoints().Num() > 0) {
						UTrapComponent* damageComponent = enemyController->GetPawn()->FindComponentByClass<UTrapComponent>();
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




