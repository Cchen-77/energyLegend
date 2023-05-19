// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GJPlayerController.h"
#include"Camera/CameraActor.h"
#include"Camera/CameraComponent.h"
#include"Kismet/GameplayStatics.h"
#include"Utils/GJPlayerStart.h"
#include"GJGameInstance.h"
#include"Blueprint/WidgetBlueprintLibrary.h"
AGJPlayerController::AGJPlayerController()
{
	bAutoManageActiveCameraTarget = false;
}

void AGJPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bCameraLocked) {
		auto PawnLocation = GetPawn()->GetActorLocation();
		RealCameraLocation = PawnLocation + FVector(0, 100, 0);
	}
	UpdateGameCamera(DeltaTime);
}

void AGJPlayerController::BeginPlay()
{
	Super::BeginPlay();
	UWidgetBlueprintLibrary::SetFocusToGameViewport();
	GameCamera = GetWorld()->SpawnActor<ACameraActor>(GameCameraClass,Startup_CameraTransform);
	GameCamera->GetCameraComponent()->SetProjectionMode(ECameraProjectionMode::Orthographic);
	RealCameraLocation = GameCamera->GetActorLocation();
	SetViewTarget(GameCamera);
	StartupWithCheckpoint();
}

void AGJPlayerController::UpdateGameCamera(float DeltaTime)
{
	auto CurLocation = GameCamera->GetActorLocation();
	auto DstLocation = FMath::VInterpTo(CurLocation, RealCameraLocation, DeltaTime, BlendSpeed);
	GameCamera->SetActorLocation(DstLocation);
}
void AGJPlayerController::StartupWithCheckpoint()
{
	TArray<AActor*> StartPots;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AGJPlayerStart::StaticClass(), StartPots);
	auto GJGI = Cast<UGJGameInstance>(GetGameInstance());
	if (!GJGI) {
		return;
	}
	FName CheckpointName = GJGI->GetCheckpoint();
	for (auto StartPot : StartPots) {
		if (Cast<AGJPlayerStart>(StartPot)->PlayerStartTag == CheckpointName) {
			GetPawn()->SetActorLocation(StartPot->GetActorLocation());
			return;
		}
	}
	return;
}