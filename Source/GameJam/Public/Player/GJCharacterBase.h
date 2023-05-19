// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include "GJCharacterBase.generated.h"

/**
 * 
 */
class AGJMovableItem;
UENUM(BlueprintType)
enum class EActionState :uint8{
	STATE_None,
	STATE_Dialog,
	STATE_Dead,
	STATE_Magic,
	STATE_Falling,
	STATE_Dash,
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
protected:
	UPROPERTY(EditDefaultsOnly,BlueprintReadWrite, Category = Energy)
		float MAX_Energy = 100;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Energy)
		float CUR_Enery = 0;
	float Cache_Z;

protected:
	UPROPERTY(VisibleAnywhere,Category = Action)
	EActionState ActionState;
	UFUNCTION(BlueprintCallable)
	void SetActionState(EActionState State);
	UFUNCTION(BlueprintCallable)
	void ClearActionState(EActionState State);
	bool bFacingRight = true;
	void UpdateFacingDirection(float velocityX);
	UFUNCTION(BlueprintCallable)
		bool CanDoAction() const;
	UFUNCTION()
		void OnMove(float Amount);
	UFUNCTION()
		void OnJump();
protected:
	UFUNCTION()
		void OnMagicStart();
	UFUNCTION()
		void OnMagicCatch();
	UFUNCTION()
		void OnMagicEnd();
	UPROPERTY()
		AGJMovableItem* CatchedItem = nullptr;
	UPROPERTY(EditDefaultsOnly, Category = Magic)
		float CatchedItemBlendingSpeed = 4;
	UPROPERTY(EditDefaultsOnly, Category = Magic)
		float MagigEnegryCostScale = 5;


};
