// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GJHUD.generated.h"

/**
 * 
 */
class UGJMainMenuWidget;
class UGJDialogWidget;
class UGJEscMenuWidget;
UENUM(BlueprintType)
enum class EGameplayState :uint8 {
	GAMEPLAY,
	MAINMENU,
};
class UUserWidget;
UCLASS()
class GAMEJAM_API AGJHUD : public AHUD
{
	GENERATED_BODY()
public:
	AGJHUD();
protected:
	virtual void BeginPlay() override;
protected:
	UPROPERTY(EditDefaultsOnly,Category = GameState)
		EGameplayState GameplayState =  EGameplayState::MAINMENU;
public:
	UFUNCTION(BlueprintCallable)
		void Open_MainMenuWidget();
	UFUNCTION(BlueprintCallable)
		void Open_EscMenuWidget();
	UFUNCTION(BlueprintCallable)
		void Close_EscMenuWidget();
	UFUNCTION(BlueprintCallable)
		void Open_DialogWidget();
	UFUNCTION(BlueprintCallable)
		void SetDialogContent(FName Name, FText Text);
	UFUNCTION(BlueprintCallable)
		void Close_DialogWidget();
	UFUNCTION(BlueprintCallable)
		void Open_EnergyBarWidget();
	UFUNCTION(BlueprintCallable)
		void Close_EnergyBarWidget();
	UFUNCTION(BlueprintCallable)
		void Start_TransitionOut(TSoftObjectPtr<UWorld> Level);
	UFUNCTION(BlueprintCallable)
		void Start_TransitionIn();
	FTimerHandle TransitionTimerHandle;
	void TransitionTo();
protected:
	UFUNCTION(BlueprintCallable)
		bool IsPendingOpening();
	TSoftObjectPtr<UWorld> Pending_OpeningLevel;
protected:
	UPROPERTY(EditDefaultsOnly, Category = Widget)
		TSubclassOf<UGJMainMenuWidget> MainMenuWidgetClass;
	UPROPERTY(EditDefaultsOnly, Category = Widget)
		TSubclassOf<UGJEscMenuWidget> EscMenuWidgetClass;
	UPROPERTY(EditDefaultsOnly, Category = Widget)
		TSubclassOf<UGJDialogWidget> DialogWidgetClass;
	UPROPERTY(EditDefaultsOnly, Category = Widget)
		TSubclassOf<UUserWidget> EnergyBarWidgetClass;
	UPROPERTY(EditDefaultsOnly, Category = Widget)
		TSubclassOf<UUserWidget> TransitionOutWidgetClass;
	UPROPERTY(EditDefaultsOnly, Category = Widget)
		TSubclassOf<UUserWidget> TransitionInWidgetClass;
	UPROPERTY()
		UGJMainMenuWidget* MainMenuWidget;
	UPROPERTY()
		UGJEscMenuWidget* EscMenuWidget;
	UPROPERTY()
		UGJDialogWidget* DialogWidget;
	UPROPERTY()
		UUserWidget* EnergyBarWidget;
	UPROPERTY()
		UUserWidget* TransitionOutWidget;
	UPROPERTY()
		UUserWidget* TransitionInWidget;
protected:
	void SetInputModeUIOnly();
	void SetInputModeGameOnly();
};
