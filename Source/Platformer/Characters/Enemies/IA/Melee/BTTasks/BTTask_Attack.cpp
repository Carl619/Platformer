// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Attack.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "../MeleeAIController.h"
#include "../../../../Player/PlayerCharacter.h"
#include "../../../Melee/MeleeEnemy.h"
#include "../../../../Components/LifeComponent.h"
#include "../../../../Components/PunchComponent.h"


EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMeleeAIController* enemyController = Cast<AMeleeAIController>(OwnerComp.GetAIOwner());

	APlayerCharacter*       player = Cast<APlayerCharacter>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(enemyController->TargetKeyID));

	if (IsValid(enemyController) && IsValid(player))
	{

		AMeleeEnemy* controlledPawn = Cast<AMeleeEnemy>(enemyController->GetPawn());

	if (IsValid(controlledPawn))
	{
	ULifeComponent*   lifeComponent = player->FindComponentByClass<ULifeComponent>();
	UPunchComponent* damageComponent = enemyController->GetPawn()->FindComponentByClass<UPunchComponent>();
	float             distance = controlledPawn->GetDistanceTo(player);

	if (IsValid(lifeComponent) && IsValid(damageComponent))
	{	
	if (distance <= controlledPawn->GetDistanceToAttack())
	{
		damageComponent->Punch();
	}
	else {
		damageComponent->StopPunch();
	}
	return EBTNodeResult::Succeeded;
	}
	}
	}
	return EBTNodeResult::Failed;
}


