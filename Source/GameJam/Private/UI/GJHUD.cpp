// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GJHUD.h"
#include"Blueprint/UserWidget.h"
#include"Blueprint/WidgetBlueprintLibrary.h"
#include"UI/GJDialogWidget.h"
#include"UI/GJEscMenuWidget.h"
#include"UI/GJMainMenuWidget.h"
#include"Kismet/GameplayStatics.h"
#include"Utils/GJPausedTimerManageTicker.h"
#include"MyDebug.h"
AGJHUD::AGJHUD()
{
}

void AGJHUD::BeginPlay()
{
	Super::BeginPlay();
	Start_TransitionIn();
	if (GameplayState == EGameplayState::GAMEPLAY) {
		Open_EnergyBarWidget();
		SetInputModeGameOnly();
	}
	else {
		SetInputModeUIOnly();
		Open_MainMenuWidget();
	}
}

void AGJHUD::Open_MainMenuWidget()
{
	if (IsPendingOpening()) return;
	if (!MainMenuWidget) {
		MainMenuWidget = CreateWidget<UGJMainMenuWidget>(GetOwningPlayerController(), MainMenuWidgetClass);
	}
	MainMenuWidget->AddToViewport();
	SetInputModeUIOnly();
	MainMenuWidget->SetFocus();
}

void AGJHUD::Open_EscMenuWidget()
{
	if (IsPendingOpening()) return;
	if (!EscMenuWidget) {
		EscMenuWidget = CreateWidget<UGJEscMenuWidget>(GetOwningPlayerController(), EscMenuWidgetClass);
	}
	EscMenuWidget->AddToViewport(2);
	SetInputModeUIOnly();
	UGameplayStatics::SetGamePaused(GetWorld(),true);
	EscMenuWidget->SetFocus();
}

void AGJHUD::Close_EscMenuWidget()
{
	if (IsPendingOpening()) return;
	if (EscMenuWidget) {
		EscMenuWidget->RemoveFromParent();
	}
	UGameplayStatics::SetGamePaused(GetWorld(), false);
	SetInputModeGameOnly();
}

void AGJHUD::Open_DialogWidget()
{
	if (IsPendingOpening()) return;
	if (!DialogWidget) {
		DialogWidget = CreateWidget<UGJDialogWidget>(GetOwningPlayerController(), DialogWidgetClass);
	}
	DialogWidget->AddToViewport();
}

void AGJHUD::SetDialogContent(FName Name, FText Text)
{
	if (IsPendingOpening()) return;
	if (DialogWidget) {
		DialogWidget->SetWho(Name);
		DialogWidget->SetContent(Text);
	}
}

void AGJHUD::Close_DialogWidget()
{
	if (IsPendingOpening()) return;
	if (DialogWidget) {
		DialogWidget->RemoveFromParent();
	}
}

void AGJHUD::Open_EnergyBarWidget()
{
	if (IsPendingOpening()) return;
	if (!EnergyBarWidget) {
		EnergyBarWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), EnergyBarWidgetClass);
	}
	EnergyBarWidget->AddToViewport();
}

void AGJHUD::Close_EnergyBarWidget()
{
	if (IsPendingOpening()) return;
	if (EnergyBarWidget) {
		EnergyBarWidget->RemoveFromParent();
	}
}

void AGJHUD::Start_TransitionOut(TSoftObjectPtr<UWorld> Level)
{
	UGameplayStatics::SetGamePaused(GetWorld(), true);
	GetWorld()->SpawnActor<AGJPausedTimerManageTicker>();
	Pending_OpeningLevel = Level;
	TransitionOutWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), TransitionOutWidgetClass);
	TransitionOutWidget->AddToViewport(10);
	GetWorld()->GetTimerManager().SetTimer(TransitionTimerHandle, this, &AGJHUD::TransitionTo, 0.5);
}
void AGJHUD::Start_TransitionIn() {
	TransitionInWidget = CreateWidget<UUserWidget>(GetOwningPlayerController(), TransitionInWidgetClass);
	TransitionInWidget->AddToViewport(10);
}
void AGJHUD::TransitionTo()
{
	UGameplayStatics::OpenLevelBySoftObjectPtr(GetWorld(), Pending_OpeningLevel);
}

bool AGJHUD::IsPendingOpening()
{
	Pending_OpeningLevel.LoadSynchronous();
	return Pending_OpeningLevel.IsValid();
}

void AGJHUD::SetInputModeUIOnly()
{
	if (auto PC = GetOwningPlayerController()) {
		PC->SetInputMode(FInputModeUIOnly());
		PC->SetShowMouseCursor(true);
	}
}

void AGJHUD::SetInputModeGameOnly()
{
	if (auto PC = GetOwningPlayerController()) {
		PC->SetInputMode(FInputModeGameOnly());
		PC->SetShowMouseCursor(false);
		UWidgetBlueprintLibrary::SetFocusToGameViewport();
	}
}
