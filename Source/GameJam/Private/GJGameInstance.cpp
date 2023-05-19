// Fill out your copyright notice in the Description page of Project Settings.


#include "GJGameInstance.h"
#include"GameFramework/GameUserSettings.h"
UGJGameInstance::UGJGameInstance()
{
}
void UGJGameInstance::Init()
{
	Super::Init();
	//Default GameUserSettings
	auto GameUserSettings = GEngine->GetGameUserSettings();
	GameUserSettings->SetFullscreenMode(EWindowMode::Windowed);
	GameUserSettings->SetFrameRateLimit(60);
	GameUserSettings->ApplySettings(false);

	CheckpointName = TEXT("Startup");

}

void UGJGameInstance::SetCheckpoint(FName Name)
{
	CheckpointName = Name;
}

FName UGJGameInstance::GetCheckpoint()
{
	return CheckpointName;
}

