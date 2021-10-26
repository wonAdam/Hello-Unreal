// Fill out your copyright notice in the Description page of Project Settings.


#include "ABGameInstance.h"

UABGameInstance::UABGameInstance()
{
	FString CharacterDataPath = TEXT("/Game/GameData/ABCharacterData.ABCharacterData");
	static ConstructorHelpers::FObjectFinder<UDataTable> DT_ABCHARACTER(*CharacterDataPath);
	ABCharacterTable = DT_ABCHARACTER.Object;
}

FABCharacterData* UABGameInstance::GetABCharacterData(int32 Level)
{
	return ABCharacterTable->FindRow<FABCharacterData>(*FString::FromInt(Level), TEXT(""));
}


void UABGameInstance::Init()
{
	Super::Init();

	ABLOG(Warning, TEXT("DropExp of Level 20 ABCharacter : %d"), GetABCharacterData(20)->DropExp);
}