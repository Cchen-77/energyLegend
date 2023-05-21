// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/GJEventBoxTrigger.h"
#include"Components/BoxComponent.h"
#include"Player/GJCharacterBase.h"
#include"Kismet/GameplayStatics.h"
#include"Player/GJPlayerController.h"
#include"PaperFlipbookComponent.h"
AGJEventBoxTrigger::AGJEventBoxTrigger()
{
	PrimaryActorTick.bCanEverTick = true;
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	SetRootComponent(BoxCollision);
	NotificationSprite = CreateDefaultSubobject<UPaperFlipbookComponent>(TEXT("NotificationSprite"));
	NotificationSprite->SetupAttachment(GetRootComponent());

}
void AGJEventBoxTrigger::BeginPlay()
{
	Super::BeginPlay();
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AGJEventBoxTrigger::EventTrigger);
	ShowTriggerNotification(false);
}

void AGJEventBoxTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bWalkingInAutoTrigger) {
		if (CharacterInAndWantsToTrigger()) {
			if (auto PC = Cast<AGJPlayerController>(UGameplayStatics::GetPlayerController(this, 0))) {
				bTriggered = true;
				PC->HandleEvent(EventIndex);
			}
		}
	}
}

void AGJEventBoxTrigger::EventTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!bWalkingInAutoTrigger) return;
	if (bTriggered && bOnlyTriggerOnce) return;
	if (Cast<ACharacter>(OtherActor) == UGameplayStatics::GetPlayerCharacter(this, 0)) {
		if (auto PC = Cast<AGJPlayerController>(UGameplayStatics::GetPlayerController(this, 0))) {
			bTriggered = true;
			PC->HandleEvent(EventIndex);
		}
	}
}

void AGJEventBoxTrigger::ShowTriggerNotification(bool Show)
{
	NotificationSprite->SetHiddenInGame(!Show);
}

bool AGJEventBoxTrigger::CharacterInAndWantsToTrigger()
{
	if (!bTriggered || !bOnlyTriggerOnce) {
		TArray<AActor*> OverlappingActors;
		auto PlayerCharacter = Cast<AGJCharacterBase>(UGameplayStatics::GetPlayerCharacter(this, 0));
		BoxCollision->GetOverlappingActors(OverlappingActors, AGJCharacterBase::StaticClass());
		for (auto OverlappingActor : OverlappingActors) {
			if (Cast<AGJCharacterBase>(OverlappingActor) == PlayerCharacter) {
				if (PlayerCharacter->CanDoAction()) {
					ShowTriggerNotification(true);
				}
				else {
					ShowTriggerNotification(false);
				}
				if (PlayerCharacter->GetActionState() == EActionState::STATE_WantsToTrigger) {
					return true;
				}
				else {
					return false;
				}
			}
		}
	}
	ShowTriggerNotification(false);
	return false;
}
