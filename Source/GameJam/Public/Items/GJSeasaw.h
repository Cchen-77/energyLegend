// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Items/GJItemBase.h"
#include "GJSeasaw.generated.h"

/**
 * 
 */
UENUM()
enum class ESeeSawState :uint8 {
	MID,
	LeftUp,
	RightUp,

};
class UFlipbook;
class UBoxComponent;
UCLASS()
class GAMEJAM_API AGJSeasaw : public AGJItemBase
{
	GENERATED_BODY()
public:
	AGJSeasaw();
	virtual void Tick(float DeltaTime) override;
	ESeeSawState SeeSawState = ESeeSawState::MID;
protected:
	UPROPERTY(VisibleAnywhere, Category = Components)
		UBoxComponent* LeftChecker;
	UPROPERTY(VisibleAnywhere, Category = Components)
		UBoxComponent* RightChecker;
	virtual void BeginPlay() override;
protected:
	UPROPERTY(EditDefaultsOnly, Category = SeeSaw)
		float BlendSpeed;
	float DstAngle;
	UPROPERTY(EditDefaultsOnly, Category = SeeSaw)
		float Angle;
	UPROPERTY(EditDefaultsOnly, Category = SeeSaw)
		float UpPower;
	UPROPERTY(EditDefaultsOnly, Category = SeeSaw)
		float EnergyAmount = 5;
	bool CheckSeeSawSide(UBoxComponent* Side);
	void UpCharacter(UBoxComponent* Side);
};
