// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/GJItemBase.h"
#include "GJBasePickup.generated.h"

/**
 * 
 */
class AGJCharacterBase;
UCLASS()
class GAMEJAM_API AGJBasePickup : public AGJItemBase
{
	GENERATED_BODY()
public:
	AGJBasePickup();
protected:
	virtual void BeginPlay() override;
protected:
	UFUNCTION(BlueprintImplementableEvent)
	void GiveTo(AGJCharacterBase* Character);
	UFUNCTION()
	void CheckPicking(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
