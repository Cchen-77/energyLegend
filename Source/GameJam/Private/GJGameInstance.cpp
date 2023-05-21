// Fill out your copyright notice in the Description page of Project Settings.


#include "GJGameInstance.h"
#include"GameFramework/GameUserSettings.h"
#include"MyDebug.h"
UGJGameInstance::UGJGameInstance()
{
}
void UGJGameInstance::Init()
{
	Super::Init();
	//Default GameUserSettings
	auto GameUserSettings = GEngine->GetGameUserSettings();
	GameUserSettings->SetFullscreenMode(EWindowMode::Windowed);
	GameUserSettings->SetFrameRateLimit(120);
	GameUserSettings->ApplySettings(false);

	CheckpointName = TEXT("Startup");
	Checkpoints.Add(TEXT("Startup"));

}

void UGJGameInstance::SetCheckpoint(FName Name)
{
	if (Checkpoints.Find(Name)==INDEX_NONE) {
		DEBUG(Name.ToString());
		CheckpointName = Name;
		Checkpoints.Add(Name);
		AddCheckpoint();
	}
}

FName UGJGameInstance::GetCheckpoint()
{
	return CheckpointName;
}

void UGJGameInstance::ResetCheckpoint()
{
	CheckpointName = TEXT("Startup");
	Checkpoints.Empty();
	Checkpoints.Add(TEXT("Startup"));
}

