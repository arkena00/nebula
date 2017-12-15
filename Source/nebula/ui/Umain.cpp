// Fill out your copyright notice in the Description page of Project Settings.

#include "ui/Umain.h"
#include "ui/Ubutton.h"
#include "game/player_controller.h"
#include "log.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "GenericPlatform/GenericPlatformMisc.h"

#include <string>
#include <vector>

std::vector<std::string> menu_list{ "Ship", "Construction", "Research" };

bool UUmain::Initialize()
{
	auto status = Super::Initialize();

	bp_check_ret(ui_button, status);

	stack_menu_->SetVisibility(ESlateVisibility::Hidden);
	
	// menu button
	for (int i = 0; i != menu_list.size(); i++)
	{
		auto btn = CreateWidget<UUbutton>(GetWorld(), ui_button);
		btn->on_click([this, i]()
		{
			// swap visibility if index is the same
			if (stack_menu_->GetActiveWidgetIndex() == i)
			{
				if (stack_menu_->GetVisibility() == ESlateVisibility::Visible) stack_menu_->SetVisibility(ESlateVisibility::Hidden);
				else stack_menu_->SetVisibility(ESlateVisibility::Visible);
			}
			else stack_menu_->SetVisibility(ESlateVisibility::Visible);

			stack_menu_->SetActiveWidgetIndex(i);
		});
		btn->text()->SetText(FText::FromString(menu_list[i].c_str()));
		box_menu_->AddChild(btn);
	}

	// bind event
	Aplayer_controller* pc = Cast<Aplayer_controller>(GetOwningPlayer());
	if (pc) pc->event_ships_update.AddDynamic(this, &UUmain::ships_update);
	if (pc) pc->event_info_update.AddDynamic(this, &UUmain::info_update);
	ships_update();
	
	return status;
}


void UUmain::info_update(FString data)
{
	info_->SetText(FText::FromString(data));
}

void UUmain::ships_update()
{

	UE_LOG(LogTemp, Warning, TEXT("ships_update"));

	//auto ship_item = CreateWidget<UUserWidget>(GetWorld(), bp_ship_item_);
	//ships_->AddChild(ship_item);

	
	Aplayer_controller* pc = Cast<Aplayer_controller>(GetOwningPlayer());
	if (pc)
	{
		ships_->ClearChildren();

		int i = 0;
		for (auto ship : pc->ships())
		{
			auto ship_item = CreateWidget<UUserWidget>(GetWorld(), ui_ship_item);

			auto btn = CreateWidget<UUbutton>(GetWorld(), ui_button);
			btn->text()->SetText(FText::FromString(FString("Take control")));
			btn->on_click([i, this]()
			{
				Cast<Aplayer_controller>(GetOwningPlayer())->server_ship_control(i);
			});

			ships_->AddChild(btn);
			i++;
		}
	}
	
}


