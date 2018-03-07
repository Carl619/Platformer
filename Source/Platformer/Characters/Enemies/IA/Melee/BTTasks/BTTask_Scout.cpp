// Fill out your copyright notice in the Description page of Project Settings.

#include "BTTask_Scout.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Blackboard/BlackboardKeyAllTypes.h"
#include "../MeleeAIController.h"
#include "../../../../Player/PlayerCharacter.h"
#include "../../../Melee/MeleeEnemy.h"
#include "../../../../Components/LifeComponent.h"
#include "../../../../Components/PunchComponent.h"
#include "Engine/TargetPoint.h"

#include "../../../Shooter/ShooterEnemy.h"
#include "../../Shooter/ShooterAIController.h"



EBTNodeResult::Type UBTTask_Scout::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	// Get the AMeleeAIController.
	AMeleeAIController* enemyController = Cast<AMeleeAIController>(OwnerComp.GetAIOwner());
	// Get the player.
	APlayerCharacter*       player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (enemyController) {
		UBlackboardComponent*blackboard = enemyController->GetBlackboardComponent();
		if (IsValid(enemyController) && IsValid(player))
		{
			AMeleeEnemy* controlledPawn = Cast<AMeleeEnemy>(enemyController->GetPawn());

			if (IsValid(controlledPawn))
			{
				/*get array of points to patrol*/
				TArray<ATargetPoint*> TargetPoints = controlledPawn->getTargetPoints();

				if (TargetPoints.Num() > 0)
				{
					/*the ai goes around all the points in a sequence and begins again*/
					enemyController->MoveToActor(TargetPoints[controlledPawn->GetCurrentTargetPoint()], 5.f, true, true, true, 0, true);
					/*when it is near enough the ai changes the point to go*/
					if (controlledPawn->GetDistanceTo(TargetPoints[controlledPawn->GetCurrentTargetPoint()]) < 120)
					{
						controlledPawn->SetCurrentTargetPoint(controlledPawn->GetCurrentTargetPoint() + 1);
						if (controlledPawn->GetCurrentTargetPoint() >= TargetPoints.Num())
							controlledPawn->SetCurrentTargetPoint(0);
						blackboard->SetValueAsObject("LocationToGo", TargetPoints[controlledPawn->GetCurrentTargetPoint()]);
					}

					return EBTNodeResult::Succeeded;
				}
			}
		}
	}
	else {
		// Get the AShooterAIController.
		AShooterAIController* ShooterController = Cast<AShooterAIController>(OwnerComp.GetAIOwner());
		
		if (IsValid(ShooterController) && IsValid(player))
		{
			UBlackboardComponent*blackboard = ShooterController->GetBlackboardComponent();
			AShooterEnemy* controlledPawn = Cast<AShooterEnemy>(ShooterController->GetPawn());

			if (IsValid(controlledPawn))
			{
				/*get array of points to patrol*/
				TArray<ATargetPoint*> TargetPoints = controlledPawn->getTargetPoints();

				if (TargetPoints.Num() > 0)
				{
					/*the ai goes around all the points in a sequence and begins again*/
					ShooterController->MoveToActor(TargetPoints[controlledPawn->GetCurrentTargetPoint()], 5.f, true, true, true, 0, true);
					/*when it is near enough the ai changes the point to go*/
					if (controlledPawn->GetDistanceTo(TargetPoints[controlledPawn->GetCurrentTargetPoint()]) < 120)
					{
						controlledPawn->SetCurrentTargetPoint(controlledPawn->GetCurrentTargetPoint() + 1);
						if (controlledPawn->GetCurrentTargetPoint() >= TargetPoints.Num())
							controlledPawn->SetCurrentTargetPoint(0);
						blackboard->SetValueAsObject("LocationToGo", TargetPoints[controlledPawn->GetCurrentTargetPoint()]);
					}

					return EBTNodeResult::Succeeded;
				}
			}
		}
	}

	return EBTNodeResult::Failed;
}