// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GJPlayerController.h"
#include"Camera/CameraActor.h"
#include"Camera/CameraComponent.h"
#include"Kismet/GameplayStatics.h"
#include"Utils/GJPlayerStart.h"
#include"GJGameInstance.h"
#include"Blueprint/WidgetBlueprintLibrary.h"
#include"Utils/GJEventManager.h"
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

	//Restart
	StartupWithCheckpoint();
	//Camera
	UWidgetBlueprintLibrary::SetFocusToGameViewport();
	GameCamera = GetWorld()->SpawnActor<ACameraActor>(GameCameraClass,Startup_CameraTransform);
	GameCamera->GetCameraComponent()->SetProjectionMode(ECameraProjectionMode::Orthographic);
	auto StartupLocation = GetPawn()->GetActorLocation();
	StartupLocation += FVector(0, 100, 0);
	GameCamera->SetActorLocation(StartupLocation);
	RealCameraLocation = GameCamera->GetActorLocation();
	SetViewTarget(GameCamera);


	//Event
	EventManager = GetWorld()->SpawnActor<AGJEventManager>(EventManagerClass);
}

void AGJPlayerController::UpdateGameCamera(float DeltaTime)
{
	auto CurLocation = GameCamera->GetActorLocation();
	auto DstLocation = FMath::VInterpTo(CurLocation, RealCameraLocation, DeltaTime, BlendSpeed);
	GameCamera->SetActorLocation(DstLocation);
}
void AGJPlayerController::HandleEvent(int index)
{
	if (EventManager) {
		EventManager->HandleEvent(index);
	}
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