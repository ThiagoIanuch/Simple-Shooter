// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"

#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

#include "Components/TextBlock.h"

void AShooterPlayerController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	if (bIsWinner)
	{
		UUserWidget* WinScreen = CreateWidget(this, WinScreenClass);

		if (WinScreen != nullptr)
		{
			WinScreen->AddToViewport();

			EndGameFocus->DisableInput(this);

			CountdownTextBlock = Cast<UTextBlock>(WinScreen->GetWidgetFromName(TEXT("TextBlock")));
		}
	}
	else
	{
		UUserWidget* LoseScreen = CreateWidget(this, LoseScreenClass);

		if (LoseScreen != nullptr)
		{
			LoseScreen->AddToViewport();

			CountdownTextBlock = Cast<UTextBlock>(LoseScreen->GetWidgetFromName(TEXT("TextBlock")));
		}
	}

	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartDelay);

	if (CountdownTextBlock != nullptr)
	{
		RemainingSeconds = 5;

		GetWorldTimerManager().SetTimer(CountdownTimerHandle, this, &AShooterPlayerController::UpdateCountdownTimer, 1.0f, true, 0.f);
	}
}

void AShooterPlayerController::UpdateCountdownTimer()
{
	FText Message = FText::FromString(FString::Printf(TEXT("Level will restart in %d seconds..."), RemainingSeconds));

	CountdownTextBlock->SetText(Message);

	RemainingSeconds--;

	if (RemainingSeconds <= 0)
	{
		GetWorldTimerManager().ClearTimer(CountdownTimerHandle);
	}
}
