// Fill out your copyright notice in the Description page of Project Settings.


#include "Items/GJSpring.h"
#include"Components/BoxComponent.h"
#include"Kismet/GameplayStatics.h"
#include"GameFramework/Character.h"
#include"GameFramework/CharacterMovementComponent.h"
#include"Player/GJCharacterBase.h"
#include"MyDebug.h"
AGJSpring::AGJSpring()
{
	TriggerBox = CreateDefaultSubobject<UBoxComponent>("TriggerBox");
	TriggerBox->SetupAttachment(GetRootComponent());
}

void AGJSpring::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AGJSpring::BeginPlay()
{
	Super::BeginPlay();
	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &AGJSpring::Trigger);
	bTriggered = false;
}

void AGJSpring::Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bTriggered) return;
	auto OtherCharacter = Cast<ACharacter>(OtherActor);
	if (OtherCharacter && OtherCharacter == UGameplayStatics::GetPlayerCharacter(this, 0)) {
		bTriggered = true;
		auto NowVelocity = OtherCharacter->GetCharacterMovement()->Velocity;
		NowVelocity.Z = 0;
		OtherCharacter->GetCharacterMovement()->Velocity = NowVelocity;
		Cast<AGJCharacterBase>(OtherCharacter)->AddEnergy(EnergyAmount);
		OtherCharacter->GetCharacterMovement()->AddImpulse(FVector(0, 0, SpringPower), true);
		GetWorld()->GetTimerManager().SetTimer(SpringupTimerHandle, this, &AGJSpring::Springup, SpringupTime, false);
	}
}

void AGJSpring::Springup()
{
	BoxCollision->SetBoxExtent(BoxExtentAfterTriggered, false);
}
