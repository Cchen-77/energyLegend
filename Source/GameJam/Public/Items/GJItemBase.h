// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GJItemBase.generated.h"
class UPaperZDAnimationComponent;
class UPaperFlipbookComponent;
class UBoxComponent;
UCLASS()
class GAMEJAM_API AGJItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGJItemBase();
	virtual void Tick(float DeltaTime) override;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
protected:
	UPROPERTY(VisibleAnywhere, Category = Components)
		UBoxComponent* BoxCollision;
	UPROPERTY(VisibleAnywhere, Category = Components)
		UPaperFlipbookComponent* Sprite;
	UPROPERTY(VisibleAnywhere, Category = Components)
		UPaperZDAnimationComponent* AnimComponent;
};
