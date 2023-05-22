// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/GJEventManager.h"
#include"Kismet/GameplayStatics.h"
#include"NPC/GJNPCBase.h"
#include"Player/GJCharacterBase.h"
#include"UI/GJHUD.h"
#include"GameFramework/CharacterMovementComponent.h"
// Sets default values
AGJEventManager::AGJEventManager()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AGJEventManager::BeginPlay()
{
	Super::BeginPlay();
	
}

void AGJEventManager::StartDialog(UDataTable* Dialog)
{
	Index = 0;
	Dialog->GetAllRows<FDialogContent>(TEXT("???"), Dialogues);
	if (auto PC = UGameplayStatics::GetPlayerController(this, 0)) {
		if (auto HUD = Cast<AGJHUD>(PC->GetHUD())) {
			HUD->Open_DialogWidget();
		}
		if (auto Character = Cast<AGJCharacterBase>(PC->GetPawn())) {
			Character->GetCharacterMovement()->Velocity = FVector(0, 0, 0);
			Character->SetActionState(EActionState::STATE_Dialog);
		}
	}
}

void AGJEventManager::EndDialog()
{
	Dialogues.Empty();
	if (auto PC = UGameplayStatics::GetPlayerController(this, 0)) {
		if (auto HUD = Cast<AGJHUD>(PC->GetHUD())) {
			HUD->Close_DialogWidget();
		}
		if (auto Character = Cast<AGJCharacterBase>(PC->GetPawn())) {
			Character->ClearActionState(EActionState::STATE_Dialog);
		}
	}
}

void AGJEventManager::MakeDialog()
{
	if (auto PC = UGameplayStatics::GetPlayerController(this, 0)) {
		if (auto HUD = Cast<AGJHUD>(PC->GetHUD())) {
			HUD->SetDialogContent(Dialogues[Index]->Who, Dialogues[Index]->Content);
		}
	}
	Index++;
}

