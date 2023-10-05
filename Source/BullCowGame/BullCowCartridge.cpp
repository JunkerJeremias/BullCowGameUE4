// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

const int ISOGRAMSSIZE = 10;

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    ShowWelcomeMessage();
    Initialise();
    ShowWinCondition();

}

UBullCowCartridge::UBullCowCartridge()
{
    srand(time(NULL));

    isograms = std::unique_ptr<FString[]>
        (new FString[ISOGRAMSSIZE]{
            TEXT("hit"),
            TEXT("bam"),
            TEXT("put"),
            TEXT("push"),
            TEXT("fart"),
            TEXT("pain"),
            TEXT("first"),
            TEXT("paint"),
            TEXT("power"),
            TEXT("polish")
            });
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (playAgainPrompted)
    {
        CheckForPlayAgain(Input);
        return;
    }
    if (!IsValidIsogram(Input))
    {
        PromptNoValidIsogram(Input);
        return;
    }

    if (Input == hiddenWord)
    {
        PromptYouWin();
        PromptPlayAgain();
        return;
    }
    SubtractOneLife();
    ShowBullsAndCows(Input);

    if (livesLeft == 0)
    {
        PromptYouLose();
        PromptPlayAgain();
        return;
    }
    ShowLivesLeft();
    
}

void UBullCowCartridge::Initialise()
{
    PickHiddenWord();
    SetLivesLeft();
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
}

void UBullCowCartridge::ShowLivesLeft()
{
    PrintLine(TEXT("You have %d lives remaining."), livesLeft);

}

void UBullCowCartridge::SubtractOneLife()
{
    livesLeft--;
}

void UBullCowCartridge::ShowBullsAndCows(const FString& Input)
{
    std::pair<int, int> result = CalculateBullsAndCows(Input);
    PrintLine(TEXT("You figured out %d bulls and %d cows."), result.first, result.second);
}

std::pair<int,int> UBullCowCartridge::CalculateBullsAndCows(const FString& Input)
{
    int bulls = 0, cows = 0;

    for (int i = 0; i < Input.Len(); i++)
    {
        if (Input.Mid(i, 1) == hiddenWord.Mid(i, 1))
        {
            cows++;
            continue;
        }
        if (hiddenWord.Contains(Input.Mid(i, 1)))
            bulls++;
    }

    return std::make_pair(bulls, cows);
}

void UBullCowCartridge::PickHiddenWord()
{ 
    int randomNumber = rand() % ISOGRAMSSIZE;
    hiddenWord = isograms[randomNumber];
}

void UBullCowCartridge::SetLivesLeft()
{
    livesLeft = hiddenWord.Len();
}

void UBullCowCartridge::CheckForPlayAgain(const FString& Input)
{
    if (Input != TEXT("yes"))
    {
        Terminal->DeactivateTerminal();
        return;
    }

    playAgainPrompted = false;
    ClearScreen();
    Initialise();
    ShowWinCondition();
}

void UBullCowCartridge::PromptPlayAgain()
{
    PrintLine(TEXT("Do you want to Play again? (Yes/No)"));
    playAgainPrompted = true;
}
