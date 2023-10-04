// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    ShowWelcomeMessage();
    Initialise();
    ShowWinCondition();

}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (!IsValidIsogram(Input))
    {
        PromptNoValidIsogram(Input);
        return;
    }

    if (Input == hiddenWord)
    {
        PromptYouWin();
        return;
    }
    livesLeft--;
    ShowLivesLeft();
    if (livesLeft == 0)
        PromptYouLose();
}

void UBullCowCartridge::Initialise()
{
    hiddenWord = "paint";
    livesLeft = 5;
}

void UBullCowCartridge::ShowWelcomeMessage()
{
    PrintLine(TEXT("The Bull Cow Game"));
}

void UBullCowCartridge::ShowWinCondition()
{
    PrintLine(TEXT("Can You guess the Hidden Isogram? It is %d characters long."), hiddenWord.Len());
    PrintLine(TEXT("You have a total of %d tries."), livesLeft);
}

void UBullCowCartridge::PromptYouWin()
{
    PrintLine(TEXT("You WIN! Congrats!"));
    Initialise();
    ShowWelcomeMessage();
}

bool UBullCowCartridge::IsValidIsogram(const FString& Input)
{
    if (Input.Len() != hiddenWord.Len())
        return false;
    if (Input.Contains(" "))
        return false;

    for (int i = 0; i< Input.Len(); i++)
    {
        if (Input.Right(Input.Len()-i-1).Contains(Input.Mid(i,1)))
            return false;
    }
    return true;
}

void UBullCowCartridge::PromptNoValidIsogram(const FString& Input)
{
    PrintLine(TEXT("Your Guess '%s' is no valid Isogram. Please try again."), *Input);
    PrintLine(TEXT("Thankfully you lost none of your lives and still have %d remaining."), livesLeft);

}

void UBullCowCartridge::PromptYouLose()
{
    PrintLine(TEXT("Unfortunately you ran out of lives."));
    PrintLine(TEXT("The Hidden word was: %s"), *hiddenWord);
    Initialise();
    ShowWinCondition();
}

void UBullCowCartridge::ShowLivesLeft()
{
    PrintLine(TEXT("Yout have %d lives remaining."), livesLeft);

}
