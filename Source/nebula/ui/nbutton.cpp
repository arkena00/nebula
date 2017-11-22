// Fill out your copyright notice in the Description page of Project Settings.

#include "nbutton.h"
#include "Runtime/UMG/Public/Blueprint/WidgetTree.h"
#include "UObject/ConstructorHelpers.h"

bool Unbutton::Initialize()
{
	auto status = Super::Initialize();
	WidgetTree->RootWidget = button_;
	button_->AddChild(text_);

	return status;
}

void Unbutton::on_click(std::function<void()> fn)
{
	on_click_ = fn;
	button_->OnClicked.AddDynamic(this, &Unbutton::click);
}

void Unbutton::click()
{
	on_click_();
}