// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    
    SetHiddenWord();
    ShowWelcomeMessage();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (Input == hiddenWord)
        PrintLine(TEXT("You WIN! Congrats!"));
}

void UBullCowCartridge::SetHiddenWord()
{
    hiddenWord = TEXT("paint");
}

void UBullCowCartridge::ShowWelcomeMessage()
{
    PrintLine(TEXT("The Bull Cow Game"));
    PrintLine(TEXT("Can You guess the Hidden Isogram? It is %d characters long."), hiddenWord.Len());

}