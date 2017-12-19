// Fill out your copyright notice in the Description page of Project Settings.

#include "Ushipyard_item.h"

#include "Components/TextBlock.h"
#include "Components/NamedSlot.h"
#include "Components/ProgressBar.h"
#include "ui/Ubutton.h"


UProgressBar* UUshipyard_item::build_progress()
{
	check(build_progress_);
	return build_progress_;
}

void UUshipyard_item::action_set(class UUbutton* action)
{
	if (action_) action_->SetContent(action);
}

void UUshipyard_item::description_set(FString value)
{
	description_set(FText::FromString(value));
}

void UUshipyard_item::description_set(FText value)
{
	if (info_) info_->SetText(value);
}
