// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/GJItemBase.h"
#include"PaperFlipbookComponent.h"
#include"PaperZDAnimationComponent.h"
#include"Components/BoxComponent.h"
AGJItemBase::AGJItemBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	SetRootComponent(BoxCollision);
	Sprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("Sprite"));
	Sprite->SetupAttachment(BoxCollision);
	AnimComponent = CreateDefaultSubobject<UPaperZDAnimationComponent>("AnimComponent");
	AnimComponent->InitRenderComponent(Sprite);
}

// Called when the game starts or when spawned
void AGJItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGJItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

