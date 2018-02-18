// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Shoot.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "../ShooterAIController.h"
#include "../../../../Player/PlayerCharacter.h"
#include "../../../Melee/MeleeEnemy.h"
#include "../../../../Components/LifeComponent.h"
#include "../../../../Components/PunchComponent.h"
#include "../../../../Components/ShootComponent.h"
#include "../../../Shooter/ShooterEnemy.h"

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent & OwnerComp, uint8 * NodeMemory)
{
	AShooterAIController* enemyController = Cast<AShooterAIController>(OwnerComp.GetAIOwner());

	APlayerCharacter*       player = Cast<APlayerCharacter>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(enemyController->TargetKeyID));

	if (IsValid(enemyController) && IsValid(player))
	{

		AShooterEnemy* controlledPawn = Cast<AShooterEnemy>(enemyController->GetPawn());

		if (IsValid(controlledPawn))
		{
			ULifeComponent*   lifeComponent = player->FindComponentByClass<ULifeComponent>();
			UShootComponent* damageComponent = enemyController->GetPawn()->FindComponentByClass<UShootComponent>();
			float             distance = controlledPawn->GetDistanceTo(player);

			if (IsValid(lifeComponent) && IsValid(damageComponent))
			{
				if (distance <= controlledPawn->GetDistanceToShoot())
				{
					damageComponent->Shoot();
				}
				return EBTNodeResult::Succeeded;
			}
		}
	}
	return EBTNodeResult::Failed;
}
