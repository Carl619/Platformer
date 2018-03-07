// Fill out your copyright notice in the Description page of Project Settings.

#include "BTService_TryToAttack.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "../MeleeAIController.h"
#include "../../Shooter/ShooterAIController.h"
#include "../../../../Player/PlayerCharacter.h"
#include "../../../Melee/MeleeEnemy.h"
#include "../../../Shooter/ShooterEnemy.h"
#include "../../../../Components/PunchComponent.h"




UBTService_TryToAttack::UBTService_TryToAttack()
{
	bCreateNodeInstance = true;
}

void UBTService_TryToAttack::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	// Get the AMeleeAIController.
	AMeleeAIController* enemyController = Cast<AMeleeAIController>(OwnerComp.GetAIOwner());


	if (enemyController) {
	// Get the player.
	APlayerCharacter*       player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
		if (IsValid(enemyController) && IsValid(player))
		{
			// Get the enemy character.
			AMeleeEnemy* controlledPawn = Cast<AMeleeEnemy>(enemyController->GetPawn());

			if (IsValid(controlledPawn))
			{
				float distance = controlledPawn->GetDistanceTo(player);
				/*if distance is less small enough he can prepare to punch*/
				if (distance <= controlledPawn->GetDistanceToAttack())
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsBool("CanAttack", true);
				}
				else
				{
					UPunchComponent* damageComponent = controlledPawn->FindComponentByClass<UPunchComponent>();
					OwnerComp.GetBlackboardComponent()->SetValueAsBool("CanAttack", false);
					damageComponent->StopPunch();
				}
			}
		}
	}
	else {
		// Get the AShooterAIController.
		AShooterAIController* ShooterController = Cast<AShooterAIController>(OwnerComp.GetAIOwner());
		APlayerCharacter*       player = Cast<APlayerCharacter>(OwnerComp.GetBlackboardComponent()->GetValue<UBlackboardKeyType_Object>(ShooterController->TargetKeyID));
		if (IsValid(ShooterController) && IsValid(player))
		{
			// Get the enemy character.
			AShooterEnemy* controlledPawn = Cast<AShooterEnemy>(ShooterController->GetPawn());

			if (IsValid(controlledPawn))
			{
				float distance = controlledPawn->GetDistanceTo(player);
				/*if distance is less small enough he can prepare to punch*/
				if (distance <= controlledPawn->GetDistanceToAttack())
				{
					OwnerComp.GetBlackboardComponent()->SetValueAsBool("CanAttack", true);
				}
				else
				{
					UPunchComponent* damageComponent = controlledPawn->FindComponentByClass<UPunchComponent>();
					OwnerComp.GetBlackboardComponent()->SetValueAsBool("CanAttack", false);
					damageComponent->StopPunch();
				}
			}
		}

	}

}
