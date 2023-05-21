// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "GJSpeechBubbleInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UGJSpeechBubbleInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class GAMEJAM_API IGJSpeechBubbleInterface
{
	GENERATED_BODY()
public:
	virtual void HideSpeechBubble() {

	}
	virtual void ShowSpeechBubble(FText Text) {

	}
};
