// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <set>
#include <memory>
#include <stdlib.h>
#include <time.h>
#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
	virtual void BeginPlay() override;
	UBullCowCartridge();

	private:
		FString hiddenWord;
		int32 livesLeft = 0;
		bool playAgainPrompted = false;
		std::unique_ptr<FString[]> isograms;

		void Initialise();
		virtual void OnInput(const FString& Input) override;
		int32 GetLivesLeft() { return livesLeft; };
		void ShowWelcomeMessage();
		void ShowWinCondition();
		void PromptYouWin();
		bool IsValidIsogram(const FString&);
		void PromptNoValidIsogram(const FString&);
		void PromptYouLose();
		void ShowLivesLeft();
		void SubtractOneLife();
		void ShowBullsAndCows(const FString&);
		std::pair<int, int> CalculateBullsAndCows(const FString&);
		void PickHiddenWord();
		void SetLivesLeft();
		void CheckForPlayAgain(const FString&);
		void PromptPlayAgain();
};
