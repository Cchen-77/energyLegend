// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/GJDialogWidget.h"
#include"Components/TextBlock.h"
void UGJDialogWidget::SetContent(FText Text)
{
	DialogContent->SetText(Text);
}

void UGJDialogWidget::SetWho(FName Name)
{
	Who->SetText(FText::FromName(Name));
}
