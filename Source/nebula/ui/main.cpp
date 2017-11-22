// Fill out your copyright notice in the Description page of Project Settings.

#include "main.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Blueprint/WidgetTree.h"
#include "ui/nbutton.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformMisc.h"
#include <string>
#include <vector>

std::vector<std::string> menu_list{ "Empire", "Construction", "Research" };

bool Umain::Initialize()
{
	auto status = Super::Initialize();
	
	
	WidgetTree->RootWidget = panel_;

	// menu button
	for (int i = 0; i != menu_list.size(); i++)
	{
		if (bp_button_)
		{
			auto btn = CreateWidget<Unbutton>(GetWorld(), bp_button_);
			btn->on_click([this, i]()
			{
				if (stack_menu_->GetActiveWidgetIndex() == i) stack_menu_->SetVisibility(ESlateVisibility::Hidden);
				else stack_menu_->SetVisibility(ESlateVisibility::Visible);

				stack_menu_->SetActiveWidgetIndex(i);
			});
			btn->text()->SetText(FText::FromString(menu_list[i].c_str()));
			box_menu_->AddChild(btn);
		}
	}

	// quit button
	auto btn = CreateWidget<Unbutton>(GetWorld(), bp_button_);
	btn->on_click([&]() { GetWorld()->GetFirstPlayerController()->ConsoleCommand("quit"); });
	btn->text()->SetText(FText::FromString("Quit"));
	slot_quit_->SetContent(btn);

	return status;
}

UTextBlock* Umain::info()
{
	return text_info_;
}