// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/GJBreakableWall.h"
#include"Components/BoxComponent.h"
#include"GameFramework/Character.h"
#include"Kismet/GameplayStatics.h"
#include"MyDebug.h"
#include"PaperFlipbookComponent.h"
AGJBreakableWall::AGJBreakableWall()
{
	BreakChecker = CreateDefaultSubobject<UBoxComponent>("BreakChecker");
	BreakChecker->SetupAttachment(GetRootComponent());
}

void AGJBreakableWall::BeginPlay()
{
	Super::BeginPlay();
	BreakChecker->OnComponentBeginOverlap.AddDynamic(this, &AGJBreakableWall::CheckBreak);
}

void AGJBreakableWall::Break()
{
	Destroy();
}

void AGJBreakableWall::CheckBreak(UPrimitiveComponent* OvserlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsBreak) return;
	auto OtherCharacter = Cast<ACharacter>(OtherActor);
	if (OtherCharacter == UGameplayStatics::GetPlayerCharacter(this, 0)) {
		FVector Velocity = OtherCharacter->GetVelocity();
		FVector WallFacingVector = GetActorForwardVector();
		float Speed = Velocity.Dot(WallFacingVector);
		if (Speed >= BreakingSpeed) {
			IsBreak = true;
			GetWorld()->GetTimerManager().SetTimer(BreakingTimer, this, &AGJBreakableWall::Break, 1, false);
			BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			Sprite->SetLooping(false);
			Sprite->SetFlipbook(Breaking);
			Sprite->PlayFromStart();
		}
	}
}

