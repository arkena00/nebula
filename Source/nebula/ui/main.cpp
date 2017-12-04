// Fill out your copyright notice in the Description page of Project Settings.

#include "main.h"
#include "game/player_controller.h"

#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Blueprint/WidgetTree.h"
#include "ui/nbutton.h"
#include "Runtime/Core/Public/GenericPlatform/GenericPlatformMisc.h"
#include <string>
#include <vector>

std::vector<std::string> menu_list{ "Ship", "Construction", "Research" };

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

	UE_LOG(LogTemp, Warning, TEXT("AddDynamic"));
	Aplayer_controller* pc = Cast<Aplayer_controller>(GetOwningPlayer());
	if (pc) pc->event_ships_update.AddDynamic(this, &Umain::ships_update);

	return status;
}


UTextBlock* Umain::info()
{
	return text_info_;
}

void Umain::ships_update()
{
	UE_LOG(LogTemp, Warning, TEXT("ships_update"));
	//auto ship_item = CreateWidget<UUserWidget>(GetWorld(), bp_ship_item_);
	//ships_->AddChild(ship_item);

	Aplayer_controller* pc = Cast<Aplayer_controller>(GetOwningPlayer());
	if (pc)
	{
		ships_->ClearChildren();

		int i = 0;
		for (auto ship : pc->ships_)
		{
			auto ship_item = CreateWidget<UUserWidget>(GetWorld(), bp_ship_item_);

			auto btn = CreateWidget<Unbutton>(GetWorld(), bp_button_);
			btn->text()->SetText(FText::FromString(FString("Take control")));
			btn->on_click([i, this]()
			{
				Cast<Aplayer_controller>(GetOwningPlayer())->server_control(i);
			});

			ships_->AddChild(ship_item);
			i++;
		}
	}
}


