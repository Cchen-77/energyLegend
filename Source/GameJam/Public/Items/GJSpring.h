// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/GJItemBase.h"
#include "GJSpring.generated.h"

/**
 * 
 */
class UPaperFlipbook;
class UBoxComponent;
UCLASS()
class GAMEJAM_API AGJSpring : public AGJItemBase
{
	GENERATED_BODY()
public:
	AGJSpring();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	UPROPERTY(EditDefaultsOnly, Category = Sprite)
		UPaperFlipbook* Extented;
protected:
	UPROPERTY(VisibleAnywhere, Category = Components)
		UBoxComponent* TriggerBox;
	bool bTriggered = false;
	UPROPERTY(EditDefaultsOnly, Category = Spring);
		FVector BoxExtentAfterTriggered;
	UPROPERTY(EditDefaultsOnly, Category = Spring)
		float SpringPower;
	UPROPERTY(EditDefaultsOnly, Category = Spring)
		float EnergyAmount = 5;
	UFUNCTION()
	void Trigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UPROPERTY(EditDefaultsOnly, Category = Spring)
		float SpringupTime = 0.2;
	UFUNCTION()
	void Springup();
	FTimerHandle SpringupTimerHandle;
};
