// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GJPlayerController.generated.h"

/**
 * 
 */
class ACameraActor;
class AGJEventManager;
UCLASS()
class GAMEJAM_API AGJPlayerController : public APlayerController
{
	GENERATED_BODY()
public:
	AGJPlayerController();
	virtual void Tick(float DeltaTime) override;
protected:
	virtual void BeginPlay() override;
protected:
	UPROPERTY(EditDefaultsOnly, Category = Camera)
		FTransform Startup_CameraTransform;
	UPROPERTY(EditDefaultsOnly, Category = Camera)
		TSubclassOf<ACameraActor> GameCameraClass;
	UPROPERTY()
		 ACameraActor* GameCamera;
	UFUNCTION()
		void UpdateGameCamera(float DeltaTime);
	UPROPERTY(EditDefaultsOnly, Category = Camera)
		float BlendSpeed;
	FVector RealCameraLocation;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Camera)
		bool bCameraLocked = true;
public:
	UFUNCTION(BlueprintCallable)
		void HandleEvent(int index);
protected:
	UPROPERTY(EditDefaultsOnly, Category = Event)
		TSubclassOf<AGJEventManager> EventManagerClass;
public:
	UPROPERTY()
		AGJEventManager* EventManager;

protected:
	void StartupWithCheckpoint();
public:
	UFUNCTION(BlueprintCallable,BlueprintImplementableEvent)
		void PlaySound(FName SoundName);
};
