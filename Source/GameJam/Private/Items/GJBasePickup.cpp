// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/GJBasePickup.h"
#include"Components/BoxComponent.h"
#include"Player/GJCharacterBase.h"
#include"Kismet/GameplayStatics.h"
#include"MyDebug.h"
AGJBasePickup::AGJBasePickup()
{
}

void AGJBasePickup::BeginPlay()
{
	Super::BeginPlay();
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AGJBasePickup::CheckPicking);
}
void AGJBasePickup::CheckPicking(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	auto Character = Cast<AGJCharacterBase>(OtherActor);
	if (Character == UGameplayStatics::GetPlayerCharacter(this, 0)) {
		GiveTo(Character);
	}
}
