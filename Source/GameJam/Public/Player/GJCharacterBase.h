// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include"Utils/GJSpeechBubbleInterface.h"
#include "GJCharacterBase.generated.h"

/**
 * 
 */
class UWidgetComponent;
class AGJMovableItem;
UENUM(BlueprintType)
enum class EActionState :uint8{
	STATE_None,
	STATE_Dialog,
	STATE_Dead,
	STATE_Magic,
	STATE_Falling,
	STATE_Dash,
	STATE_WantsToTrigger,

};
UCLASS()
class GAMEJAM_API AGJCharacterBase : public APaperZDCharacter
{
	GENERATED_BODY()
public:
	AGJCharacterBase();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
public:
	UFUNCTION(BlueprintCallable)
	void AddEnergy(float Amount);
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = Energy)
		float MAX_Energy = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Energy)
		float CUR_Energy = 0;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Energy)
		float EnergyCostScale;
	float Cache_Z;

public:
	UFUNCTION(BlueprintCallable)
		bool CanDoAction() const;
	UFUNCTION(BlueprintCallable)
		EActionState GetActionState();
	UFUNCTION(BlueprintCallable)
		void SetActionState(EActionState State);
	UFUNCTION(BlueprintCallable)
		void ClearActionState(EActionState State);
protected:
	UPROPERTY(VisibleAnywhere,Category = Action)
	EActionState ActionState;
	UPROPERTY(BlueprintReadWrite)
	bool bFacingRight = true;
	void UpdateFacingDirection(float velocityX);
	UFUNCTION()
		void OnMove(float Amount);
	UFUNCTION()
		void OnJump();
	UFUNCTION()
		void OnWantsToTrigger();
	FTimerHandle WantsToTriggerTimerHandle;
	UFUNCTION()
		void OnWantsToTriggerFinish();
public:
	UFUNCTION(BlueprintCallable)
		void OnPlayerDie();
	UPROPERTY(EditDefaultsOnly)
		TSoftObjectPtr<UWorld> MainMap;
protected:
	UFUNCTION()
		void OnMagicStart();
	UFUNCTION()
		void OnMagicCatch();
	UFUNCTION()
		void OnMagicEnd();
	UPROPERTY()
		AGJMovableItem* CatchedItem = nullptr;
	FVector DstCatchedItemLocationCache;
	UPROPERTY(EditDefaultsOnly, Category = Magic)
		float CatchedItemBlendingSpeed = 4;
	UPROPERTY(EditDefaultsOnly, Category = Magic)
		float MagigEnegryCost = 5;
};
