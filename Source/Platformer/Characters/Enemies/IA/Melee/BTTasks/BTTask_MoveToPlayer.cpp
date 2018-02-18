// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_MoveToPlayer.h"
#include "Navigation/PathFollowingComponent.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "../MeleeAIController.h"
#include "../../../../Player/PlayerCharacter.h"
#include "../../../Melee/MeleeEnemy.h"

#include "../../../Shooter/ShooterEnemy.h"
#include "../../Shooter/ShooterAIController.h"





EBTNodeResult::Type UBTTask_MoveToPlayer::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{

	AMeleeAIController* enemyController = Cast<AMeleeAIController>(OwnerComp.GetAIOwner());



	if (enemyController) {
		APlayerCharacter*       player = Cast<APlayerCharacter>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(enemyController->TargetKeyID));
		if (IsValid(enemyController) && IsValid(player))
		{

			AMeleeEnemy* controlledPawn = Cast<AMeleeEnemy>(enemyController->GetPawn());

			if (IsValid(controlledPawn))
			{
				if (OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target") != nullptr)
				{
					if (player->GetUniqueID() != OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target")->GetUniqueID())
					{
						enemyController->StopMovement();
					}

					enemyController->MoveToActor(player, 5.f, true, true, true, 0, true);
				}

				return EBTNodeResult::Succeeded;
			}
		}
	}
	else {
		AShooterAIController* ShooterController = Cast<AShooterAIController>(OwnerComp.GetAIOwner());
		APlayerCharacter*       player = Cast<APlayerCharacter>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(ShooterController->TargetKeyID));
		if (IsValid(ShooterController) && IsValid(player))
		{

			AShooterEnemy* controlledPawn = Cast<AShooterEnemy>(ShooterController->GetPawn());

			if (IsValid(controlledPawn))
			{
				if (OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target") != nullptr)
				{
					if (player->GetUniqueID() != OwnerComp.GetBlackboardComponent()->GetValueAsObject("Target")->GetUniqueID())
					{
						ShooterController->StopMovement();
					}

					ShooterController->MoveToActor(player, 5.f, true, true, true, 0, true);
				}

				return EBTNodeResult::Succeeded;
			}
		}
	}

	return EBTNodeResult::Failed;
}
