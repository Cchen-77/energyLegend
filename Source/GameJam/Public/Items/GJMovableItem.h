// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include"Items/GJItemBase.h"
#include "GJMovableItem.generated.h"
class UPaperZDAnimationComponent;
class UPaperFlipbookComponent;
class UProjectileMovementComponent;
class UBoxComponent;
UCLASS()
class GAMEJAM_API AGJMovableItem :public AGJItemBase
{
	GENERATED_BODY()
	
public:	
	AGJMovableItem();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
protected:
	UPROPERTY(VisibleAnywhere, Category = Components)
		UProjectileMovementComponent* ProjectileMovement;
	UFUNCTION()
		void ItemStop(const FHitResult& ImpactResult);
public:
	bool bBeingCatched = false;
	void MagicCatching_Start();
	void MagicCatching_End();
};
