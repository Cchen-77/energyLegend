// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/GJMovableItem.h"
#include"GameFramework/ProjectileMovementComponent.h"
#include"PaperZDAnimationComponent.h"
#include"Components/BoxComponent.h"
#include"PaperZDAnimationComponent.h"
#include"Kismet/GameplayStatics.h"
#include"GameFramework/Character.h"
AGJMovableItem::AGJMovableItem()
{
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->SetUpdatedComponent(BoxCollision);
}

void AGJMovableItem::BeginPlay()
{
	Super::BeginPlay();
	ProjectileMovement->OnProjectileStop.AddDynamic(this, &AGJMovableItem::ItemStop);
}
void AGJMovableItem::ItemStop(const FHitResult& ImpactResult)
{
	if (ImpactResult.bBlockingHit) {
		auto TheActor = ImpactResult.GetActor();
		if (Cast<ACharacter>(TheActor)||Cast<AGJItemBase>(TheActor)){
			ProjectileMovement->SetUpdatedComponent(GetRootComponent());
			ProjectileMovement->Velocity = FVector(0, 0, 100);
		}

	}
}
void AGJMovableItem::MagicCatching_Start()
{
	bBeingCatched = true;
	ProjectileMovement->UpdatedComponent = nullptr;
}
void AGJMovableItem::MagicCatching_End()
{
	bBeingCatched = false;
	ProjectileMovement->SetUpdatedComponent(BoxCollision);
}
void AGJMovableItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

