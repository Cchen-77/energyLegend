// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GJEventBoxTrigger.generated.h"

class UBoxComponent;
class UPaperFlipbookComponent;
UCLASS()
class GAMEJAM_API AGJEventBoxTrigger : public AActor
{
	GENERATED_BODY()
public:	
	AGJEventBoxTrigger();

protected:
	virtual void BeginPlay() override;
protected:
	virtual void Tick(float DeltaTime) override;
	UPROPERTY(VisibleAnywhere, Category = Components)
		UBoxComponent* BoxCollision;
	UPROPERTY(VisibleAnywhere, Category = Components)
		UPaperFlipbookComponent* NotificationSprite;
protected:
	UPROPERTY(EditAnywhere, Category = Event)
		bool bWalkingInAutoTrigger = true;
	UPROPERTY(EditAnywhere, Category = Event)
		int EventIndex;
	UPROPERTY(EditAnywhere, Category = Event)
		bool bOnlyTriggerOnce;
	bool bTriggered = false;
	UFUNCTION()
	void EventTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	void ShowTriggerNotification(bool Show);
	bool CharacterInAndWantsToTrigger();
};
