// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GJCharacterBase.h"
#include"MyDebug.h"
#include"PaperFlipbookComponent.h"
#include"GameFramework/CharacterMovementComponent.h"
#include"Items/GJMovableItem.h"
#include"Components/WidgetComponent.h"
#include"UI/GJDialogWidget.h"
#include"Blueprint/WidgetBlueprintLibrary.h"
#include"Kismet/GameplayStatics.h"
#include"UI/GJHUD.h"
AGJCharacterBase::AGJCharacterBase()
{
	
}

void AGJCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//ABOUT LOCOMOTION
	UpdateFacingDirection(GetVelocity().X);

	//Magic
	if (ActionState == EActionState::STATE_Magic) {
		auto PC = Cast<APlayerController>(GetController());
		double temp1,temp2;
		if (PC&&CatchedItem) {
			FVector WorldLocation, WorldDirection;
			//update mouse location
			if (PC->GetMousePosition(temp1, temp2)) {
				PC->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
				DstCatchedItemLocationCache = CatchedItem->GetActorLocation();
				DstCatchedItemLocationCache.X = WorldLocation.X;
				DstCatchedItemLocationCache.Z = WorldLocation.Z;
			}
			FVector OldLocation = CatchedItem->GetActorLocation();
			FVector ResultLocation = FMath::VInterpTo(OldLocation, DstCatchedItemLocationCache, DeltaTime, CatchedItemBlendingSpeed);
			FHitResult Hit;
			CatchedItem->SetActorLocation(ResultLocation, true,&Hit);
		}
	}
	//ABOUT ENERGY
	float Now_Z = GetActorLocation().Z;
	CUR_Energy -= (Now_Z - Cache_Z)*EnergyCostScale;
	Cache_Z = Now_Z;
	//tricky compensate
	if (CUR_Energy > MAX_Energy + 2) {
		CUR_Energy = MAX_Energy + 2;
	}
	if (CUR_Energy <= 0) {
		//TODO: Player Death
		OnPlayerDie();
	}

}

void AGJCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	Cache_Z = GetActorLocation().Z;

}

void AGJCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("Move"), this, &AGJCharacterBase::OnMove);
	PlayerInputComponent->BindAction(TEXT("Jump"),IE_Pressed,this,&AGJCharacterBase::OnJump);
	PlayerInputComponent->BindAction(TEXT("Magic"), IE_Pressed, this, &AGJCharacterBase::OnMagicStart);
	PlayerInputComponent->BindAction(TEXT("MagicCatch"), IE_Pressed, this, &AGJCharacterBase::OnMagicCatch);
	PlayerInputComponent->BindAction(TEXT("WantsToTrigger"), IE_Pressed, this, &AGJCharacterBase::OnWantsToTrigger);
}

void AGJCharacterBase::AddEnergy(float Amount)
{
	CUR_Energy = FMath::Clamp<float>(CUR_Energy + Amount, 0, MAX_Energy);
}

EActionState AGJCharacterBase::GetActionState()
{
	return ActionState;
}

void AGJCharacterBase::SetActionState(EActionState State)
{
	ActionState = State;
}

void AGJCharacterBase::ClearActionState(EActionState State)
{
	if (ActionState == State) {
		ActionState = EActionState::STATE_None;
	}
}

void AGJCharacterBase::UpdateFacingDirection(float velocityX)
{
	if (velocityX < 0 && bFacingRight) {
		bFacingRight = false;	
		GetSprite()->SetRelativeScale3D(FVector(-1, 1, 1));
	}
	else if (velocityX > 0 && !bFacingRight) {
		bFacingRight = true;
		GetSprite()->SetRelativeScale3D(FVector(1, 1, 1));
	}
}

bool AGJCharacterBase::CanDoAction() const
{
	if (ActionState != EActionState::STATE_None) return  false;
	return true;
}

void AGJCharacterBase::OnMove(float Amount)
{
	if (!CanDoAction()) return;
	AddMovementInput(FVector(1, 0, 0), Amount);
}

void AGJCharacterBase::OnJump()
{
	if (!CanDoAction()) return;
	Jump();
}

void AGJCharacterBase::OnWantsToTrigger()
{
	if (!CanDoAction()) return;
	SetActionState(EActionState::STATE_WantsToTrigger);
	GetWorld()->GetTimerManager().SetTimer(WantsToTriggerTimerHandle, this, &AGJCharacterBase::OnWantsToTriggerFinish, 0.2, false);
}

void AGJCharacterBase::OnWantsToTriggerFinish()
{
	ClearActionState(EActionState::STATE_WantsToTrigger);
}

void AGJCharacterBase::OnPlayerDie()
{
	if (ActionState == EActionState::STATE_Dead) return;
	OnMagicEnd();
	SetActionState(EActionState::STATE_Dead);
	if (auto PC = Cast<APlayerController>(GetController())) {
		DisableInput(PC);
		if (auto HUD = Cast<AGJHUD>(PC->GetHUD())) {
			HUD->Start_TransitionOut(MainMap);
		}
	}
}

void AGJCharacterBase::OnMagicStart()
{
	if (CanDoAction()) {
		SetActionState(EActionState::STATE_Magic);
		if (auto PC = Cast<APlayerController>(GetController())) {
			PC->SetShowMouseCursor(true);
		}
	}
	else if (ActionState == EActionState::STATE_Magic) {
		OnMagicEnd();
	}
}

void AGJCharacterBase::OnMagicCatch()
{
	if (CUR_Energy <= MagigEnegryCost) {
		return;
	}
	if (ActionState != EActionState::STATE_Magic) return;
	if (CatchedItem) return;
	if (auto PC = Cast<APlayerController>(GetController())) {
		FVector WorldLocation, WorldDirection;
		PC->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
		TArray<FHitResult> OutHits;
		GetWorld()->LineTraceMultiByProfile(OutHits, WorldLocation, WorldLocation + 2000 * WorldDirection, "BlockAll");
		for (auto Hit : OutHits) {
			if (Hit.bBlockingHit) {
				if (auto MovableItem = Cast<AGJMovableItem>(Hit.GetActor())) {
					CatchedItem = MovableItem;
					CatchedItem->MagicCatching_Start();
					CUR_Energy -= MagigEnegryCost;
					return;
				}
			}
		}
	}
}

void AGJCharacterBase::OnMagicEnd()
{
	ClearActionState(EActionState::STATE_Magic);
	if (auto PC = Cast<APlayerController>(GetController())) {
		UWidgetBlueprintLibrary::SetFocusToGameViewport();
		PC->SetShowMouseCursor(false);
		PC->SetInputMode(FInputModeGameOnly());
	}
	if (CatchedItem) {
		CatchedItem->MagicCatching_End();
		CatchedItem = nullptr;
	}
}

