// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include"Engine/DataTable.h"
#include"Utils/GJSpeechBubbleInterface.h"
#include "GJEventManager.generated.h"

USTRUCT(BlueprintType)
struct FDialogContent :public FTableRowBase {
	GENERATED_BODY()
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FName Who;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FText Content;
};

UCLASS()
class GAMEJAM_API AGJEventManager : public AActor
{
	GENERATED_BODY()
public:	
	AGJEventManager();
public:
	UFUNCTION(BlueprintImplementableEvent)
		void HandleEvent(int index);
protected:
	virtual void BeginPlay() override;
public:
	
	UPROPERTY(BlueprintReadWrite, Category = Dialog)
		int Index = 0;
	TArray<FDialogContent*> Dialogues;
	UFUNCTION(BlueprintCallable)
		void StartDialog(UDataTable* Dialog);
	UFUNCTION(BlueprintCallable)
		void EndDialog();
	UFUNCTION(BlueprintCallable)
		void MakeDialog();

};
