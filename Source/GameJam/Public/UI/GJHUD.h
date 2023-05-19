// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "GJHUD.generated.h"

/**
 * 
 */
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
	UPROPERTY(EditDefaultsOnly, Category = Widgets)
		TArray<TSubclassOf<UUserWidget>> StartupWidgetClasses;
	UPROPERTY()
		TArray<UUserWidget*> StartupWidgets;
};
