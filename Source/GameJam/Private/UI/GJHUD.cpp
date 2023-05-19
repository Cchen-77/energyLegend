// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GJHUD.h"
#include"Blueprint/UserWidget.h"
AGJHUD::AGJHUD()
{
}

void AGJHUD::BeginPlay()
{
	Super::BeginPlay();
	for (auto StartupWidgetClass : StartupWidgetClasses) {
		StartupWidgets.Add(CreateWidget<UUserWidget>(GetOwningPlayerController(), StartupWidgetClass));
	}
}
