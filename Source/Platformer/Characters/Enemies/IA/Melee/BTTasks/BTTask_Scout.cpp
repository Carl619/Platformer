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
<<<<<<< HEAD
#include "../../../Shooter/ShooterEnemy.h"
#include "../../Shooter/ShooterAIController.h"
=======
>>>>>>> origin/master


EBTNodeResult::Type UBTTask_Scout::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AMeleeAIController* enemyController = Cast<AMeleeAIController>(OwnerComp.GetAIOwner());
	APlayerCharacter*       player = Cast<APlayerCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn());
<<<<<<< HEAD


	if (enemyController) {
		UBlackboardComponent*blackboard = enemyController->GetBlackboardComponent();
		if (IsValid(enemyController) && IsValid(player))
		{
			AMeleeEnemy* controlledPawn = Cast<AMeleeEnemy>(enemyController->GetPawn());

			if (IsValid(controlledPawn))
			{
				TArray<ATargetPoint*> TargetPoints = controlledPawn->getTargetPoints();

				if (TargetPoints.Num() > 0)
				{
					enemyController->MoveToActor(TargetPoints[controlledPawn->GetCurrentTargetPoint()], 5.f, true, true, true, 0, true);

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
		AShooterAIController* ShooterController = Cast<AShooterAIController>(OwnerComp.GetAIOwner());
		UBlackboardComponent*blackboard = ShooterController->GetBlackboardComponent();
		if (IsValid(ShooterController) && IsValid(player))
		{
			AShooterEnemy* controlledPawn = Cast<AShooterEnemy>(ShooterController->GetPawn());

			if (IsValid(controlledPawn))
			{
				TArray<ATargetPoint*> TargetPoints = controlledPawn->getTargetPoints();

				if (TargetPoints.Num() > 0)
				{
					ShooterController->MoveToActor(TargetPoints[controlledPawn->GetCurrentTargetPoint()], 5.f, true, true, true, 0, true);

					if (controlledPawn->GetDistanceTo(TargetPoints[controlledPawn->GetCurrentTargetPoint()]) < 120)
					{
						controlledPawn->SetCurrentTargetPoint(controlledPawn->GetCurrentTargetPoint() + 1);
						if (controlledPawn->GetCurrentTargetPoint() >= TargetPoints.Num())
							controlledPawn->SetCurrentTargetPoint(0);
						blackboard->SetValueAsObject("LocationToGo", TargetPoints[controlledPawn->GetCurrentTargetPoint()]);
					}

					return EBTNodeResult::Succeeded;
				}
=======
	UBlackboardComponent*blackboard = enemyController->GetBlackboardComponent();

	if (IsValid(enemyController) && IsValid(player))
	{
		AMeleeEnemy* controlledPawn = Cast<AMeleeEnemy>(enemyController->GetPawn());

		if (IsValid(controlledPawn))
		{
			TArray<ATargetPoint*> TargetPoints = controlledPawn->getTargetPoints();

			if (TargetPoints.Num() > 0)
			{
				enemyController->MoveToActor(TargetPoints[controlledPawn->GetCurrentTargetPoint()], 5.f, true, true, true, 0, true);

				if (controlledPawn->GetDistanceTo(TargetPoints[controlledPawn->GetCurrentTargetPoint()]) < 120)
				{
					controlledPawn->SetCurrentTargetPoint(controlledPawn->GetCurrentTargetPoint()+1);
					if (controlledPawn->GetCurrentTargetPoint() >= TargetPoints.Num())
						controlledPawn->SetCurrentTargetPoint(0);
					blackboard->SetValueAsObject("LocationToGo", TargetPoints[controlledPawn->GetCurrentTargetPoint()]);
				}

				return EBTNodeResult::Succeeded;
>>>>>>> origin/master
			}
		}
	}

	return EBTNodeResult::Failed;
}