// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ShooterCharacter.h"
#include "BrainComponent.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	
	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);

		GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
	}
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AShooterAIController::IsDead() const
{
	AShooterCharacter* ControlledCharacter = Cast<AShooterCharacter>(GetPawn());

	if (ControlledCharacter != nullptr)
	{
		return ControlledCharacter->IsDead();
	}

	return true;
}

void AShooterAIController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	if (GetBrainComponent())
	{
		GetBrainComponent()->StopLogic(TEXT("GameEnded"));
	}
}