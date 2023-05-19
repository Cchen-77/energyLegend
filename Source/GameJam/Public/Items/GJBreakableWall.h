// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/GJItemBase.h"
#include "GJBreakableWall.generated.h"

/**
 * 
 */
class UBoxComponent;
UCLASS()
class GAMEJAM_API AGJBreakableWall : public AGJItemBase
{
	GENERATED_BODY()
public:
	AGJBreakableWall();
protected:
	virtual void BeginPlay() override;
protected:
	UPROPERTY(VisibleAnywhere, Category = Components)
		UBoxComponent* BreakChecker;
	UFUNCTION()
	void CheckBreak(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UPROPERTY(EditAnywhere, Category = Breaking)
		float BreakingSpeed = 400.0f;
};
