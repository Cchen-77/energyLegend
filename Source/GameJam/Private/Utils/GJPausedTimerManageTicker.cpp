// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/GJPausedTimerManageTicker.h"

AGJPausedTimerManageTicker::AGJPausedTimerManageTicker(){
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AGJPausedTimerManageTicker::BeginPlay()
{
	Super::BeginPlay();
}

void AGJPausedTimerManageTicker::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (GetWorld()->IsPaused()) {
		GetWorld()->GetTimerManager().Tick(DeltaTime);
	}
}

