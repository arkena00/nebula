// Fill out your copyright notice in the Description page of Project Settings.

#include "ui/Ubutton.h"
#include "Blueprint/WidgetTree.h"
#include "UObject/ConstructorHelpers.h"

bool UUbutton::Initialize()
{
	auto status = Super::Initialize();
	WidgetTree->RootWidget = button_;
	button_->AddChild(text_);

	return status;
}

void UUbutton::on_click(std::function<void()> fn)
{
	on_click_ = fn;
	button_->OnClicked.AddDynamic(this, &UUbutton::click);
}

void UUbutton::click()
{
	on_click_();
}