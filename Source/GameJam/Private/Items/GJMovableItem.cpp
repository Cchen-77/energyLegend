// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/GJMovableItem.h"
#include"GameFramework/ProjectileMovementComponent.h"
#include"PaperZDAnimationComponent.h"
#include"Components/BoxComponent.h"
#include"PaperZDAnimationComponent.h"
AGJMovableItem::AGJMovableItem()
{
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->SetUpdatedComponent(BoxCollision);
}

void AGJMovableItem::BeginPlay()
{
	Super::BeginPlay();
}
void AGJMovableItem::MagicCatching_Start()
{
	ProjectileMovement->UpdatedComponent = nullptr;
}
void AGJMovableItem::MagicCatching_End()
{
	ProjectileMovement->SetUpdatedComponent(BoxCollision);
}
void AGJMovableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

