// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "GJDialogWidget.generated.h"

/**
 * 
 */
class UTextBlock;
UCLASS()
class GAMEJAM_API UGJDialogWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetContent(FText Text);
	void SetWho(FName Name);
protected:
	UPROPERTY(meta = (BindWidget))
		UTextBlock* DialogContent;
	UPROPERTY(meta = (BindWidget))
		UTextBlock* Who;
};
