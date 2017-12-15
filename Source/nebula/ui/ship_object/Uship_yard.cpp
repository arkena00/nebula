// Fill out your copyright notice in the Description page of Project Settings.

#include "Uship_yard.h"
#include "ui/Uship_object.h"
#include "ui/Ubutton.h"
#include "game.h"

#include "game/player_controller.h"

#include "UObject/ConstructorHelpers.h"
#include "world/ship_object/Areactor_solar.h"
#include "log.h"

UUship_yard::UUship_yard()
{
	ui_ship_object_ = ConstructorHelpers::FObjectFinder<UClass>(TEXT("WidgetBlueprint'/Game/nebula/ui/ui_ship_object.ui_ship_object_C'")).Object;
	ui_button_ = ConstructorHelpers::FObjectFinder<UClass>(TEXT("WidgetBlueprint'/Game/nebula/ui/ui_button.ui_button_C'")).Object;
}

void UUship_yard::init(Aship_object*)
{
	bp_check(ui_ship_object_);

	// auto data = ship_object_data::get(ship_objects::ship_yard);
	// data.description;
	description_set(FText::FromString("The ship yard is used to build ships"));

	for (auto object : neb::ship_object::get())
	{
		auto ship_object_build = CreateWidget<UUship_object>(GetWorld(), ui_ship_object_);
		std::string info;
		info += "\nname : " + object.name;
		info += "\nbuild time : " + std::to_string(object.build_time);

		auto button = CreateWidget<UUbutton>(GetWorld(), ui_button_);
		button->text()->SetText(FText::FromString("Build"));
		button->on_click([&, this]()
		{
			FString pinfo(object.name.c_str());
			pinfo += "aze";
			Cast<Aplayer_controller>(GetOwningPlayer())->log(pinfo);
			//server_ship_object_build(id);
		});
		ship_object_build->action_set(button);

		ship_object_build->description_set(info.c_str());
		objects_->AddChild(ship_object_build);
	}

}
