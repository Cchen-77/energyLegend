// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/GJCharacterBase.h"
#include"MyDebug.h"
#include"PaperFlipbookComponent.h"
#include"GameFramework/CharacterMovementComponent.h"
#include"Items/GJMovableItem.h"
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
		FVector WorldLocation, WorldDirection;
		auto PC = Cast<APlayerController>(GetController());
		PC->DeprojectMousePositionToWorld(WorldLocation, WorldDirection);
		if (CatchedItem) {
			FVector OldLocation = CatchedItem->GetActorLocation();
			FVector DstLocation = CatchedItem->GetActorLocation();
			DstLocation.X = WorldLocation.X;
			DstLocation.Z = WorldLocation.Z;
			DstLocation = FMath::VInterpTo(OldLocation, DstLocation, DeltaTime, CatchedItemBlendingSpeed);
			FHitResult Hit;
			CatchedItem->SetActorLocation(DstLocation, true,&Hit);
			CUR_Enery -= MagigEnegryCostScale*DeltaTime;
		}
	}
	//ABOUT ENERGY
	float Now_Z = GetActorLocation().Z;
	CUR_Enery -= Now_Z - Cache_Z;
	Cache_Z = Now_Z;
	//tricky compensate
	if (CUR_Enery > MAX_Energy + 2) {
		CUR_Enery = MAX_Energy + 2;
	}
	if (CUR_Enery <= 0) {
		//TODO: Player Death
		DEBUG(TEXT("EneryZero"));
		OnMagicEnd();
	}

}

void AGJCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
	CUR_Enery = MAX_Energy;
	Cache_Z = GetActorLocation().Z;
}

void AGJCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis(TEXT("Move"), this, &AGJCharacterBase::OnMove);
	PlayerInputComponent->BindAction(TEXT("Jump"),IE_Pressed,this,&AGJCharacterBase::OnJump);
	PlayerInputComponent->BindAction(TEXT("Magic"), IE_Pressed, this, &AGJCharacterBase::OnMagicStart);
	PlayerInputComponent->BindAction(TEXT("Magic"), IE_Released, this, &AGJCharacterBase::OnMagicEnd);
	PlayerInputComponent->BindAction(TEXT("MagicCatch"), IE_Pressed, this, &AGJCharacterBase::OnMagicCatch);
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

void AGJCharacterBase::OnMagicStart()
{
	SetActionState(EActionState::STATE_Magic);
	if (auto PC = Cast<APlayerController>(GetController())) {
		PC->SetShowMouseCursor(true);
	}
}

void AGJCharacterBase::OnMagicCatch()
{
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
					return;
				}
			}
		}
	}
}

void AGJCharacterBase::OnMagicEnd()
{
	ClearActionState(EActionState::STATE_Magic);
	if (CatchedItem) {
		CatchedItem->MagicCatching_End();
		CatchedItem = nullptr;
	}
	if (auto PC = Cast<APlayerController>(GetController())) {
		PC->SetShowMouseCursor(false);
	}
}
