// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GJGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GAMEJAM_API UGJGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	UGJGameInstance();
	virtual void Init() override;
public:
	UFUNCTION(BlueprintCallable)
	void SetCheckpoint(FName Name);
	UFUNCTION(BlueprintCallable)
	FName GetCheckpoint();
protected:
	UPROPERTY(EditDefaultsOnly, Category = Checkpoint)
		FName CheckpointName;
};
