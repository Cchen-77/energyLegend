// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperZDCharacter.h"
#include"Utils/GJSpeechBubbleInterface.h"
#include "GJNPCBase.generated.h"

/**
 * 
 */
class UWidgetComponent;
UCLASS()
class GAMEJAM_API AGJNPCBase : public APaperZDCharacter
{
	GENERATED_BODY()
public:
	AGJNPCBase();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = NPC)
		FName NPCName;
};
