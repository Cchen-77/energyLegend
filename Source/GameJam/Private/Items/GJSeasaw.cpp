// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/GJSeasaw.h"
#include"Components/BoxComponent.h"
#include"Items/GJMovableItem.h"
#include"Player/GJCharacterBase.h"
#include"GameFramework/CharacterMovementComponent.h"
#include"MyDebug.h"
AGJSeasaw::AGJSeasaw()
{
	LeftChecker = CreateDefaultSubobject<UBoxComponent>(TEXT("LeftChecker"));
	LeftChecker->SetupAttachment(GetRootComponent());
	RightChecker = CreateDefaultSubobject<UBoxComponent>(TEXT("RightChecker"));
	RightChecker->SetupAttachment(GetRootComponent());
}

void AGJSeasaw::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	bool Left = CheckSeeSawSide(LeftChecker);
	bool Right = CheckSeeSawSide(RightChecker);
	float NowAngle = GetActorRotation().Pitch;
	NowAngle = FMath::Lerp(NowAngle, DstAngle, BlendSpeed * DeltaTime);
	SetActorRotation(FRotator(NowAngle, 0, 0));
	if(Left&&SeeSawState!=ESeeSawState::RightUp){
		DstAngle = -Angle;
		UpCharacter(RightChecker);
		SeeSawState = ESeeSawState::RightUp;
	}
	else if (Right && SeeSawState != ESeeSawState::LeftUp) {
		DstAngle = Angle;
		UpCharacter(LeftChecker);
		SeeSawState = ESeeSawState::LeftUp;
	}
	if (!Left && !Right) {
		DstAngle = 0;
		SeeSawState = ESeeSawState::MID;
	}
}

void AGJSeasaw::BeginPlay()
{
	Super::BeginPlay();

}
bool AGJSeasaw::CheckSeeSawSide(UBoxComponent* Side)
{
	bool Hav = false;
	TArray<AActor*> OutActors;
	Side->GetOverlappingActors(OutActors, AGJMovableItem::StaticClass());
	for (auto OutActor : OutActors) {
		if (auto Item = Cast<AGJMovableItem>(OutActor)) {
			if (Item->bBeingCatched) continue;
			Hav = true;
			break;
		}
	}
	return Hav;
}

void AGJSeasaw::UpCharacter(UBoxComponent* Side)
{
	TArray<AActor*> OutActors;
	Side->GetOverlappingActors(OutActors, AGJCharacterBase::StaticClass());
	for (auto OutActor : OutActors) {
		if (auto Character = Cast<AGJCharacterBase>(OutActor)) {
			auto NowVelocity = Character->GetCharacterMovement()->Velocity;
			NowVelocity.Z = 0;
			Character->GetCharacterMovement()->Velocity = NowVelocity;
			Character->AddEnergy(EnergyAmount);
			auto Location = Character->GetActorLocation();
			Location.Z += 50;
			Character->SetActorLocation(Location);
			Character->GetCharacterMovement()->AddImpulse(FVector(0, 0, UpPower),true);
		}
	}
}
