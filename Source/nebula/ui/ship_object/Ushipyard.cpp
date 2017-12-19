// Fill out your copyright notice in the Description page of Project Settings.

#include "Ushipyard.h"
#include "ui/ship_object/Ushipyard_item.h"
#include "ui/Ubutton.h"

#include "game.h"
#include "database.hpp"

#include "game/player_controller.h"
#include "world/ship_object/Areactor_solar.h"
#include "world/ship_object/Ashipyard.h"

#include "UObject/ConstructorHelpers.h"
#include "log.h"


UUshipyard::UUshipyard()
{
	ui_shipyard_item_ = ConstructorHelpers::FObjectFinder<UClass>(TEXT("WidgetBlueprint'/Game/nebula/ui/ship_object/ui_shipyard_item.ui_shipyard_item_C'")).Object;
	ui_button_ = ConstructorHelpers::FObjectFinder<UClass>(TEXT("WidgetBlueprint'/Game/nebula/ui/ui_button.ui_button_C'")).Object;
}

void UUshipyard::init(Aship_object* ship_object)
{
	UUship_object::init(ship_object);

	bp_check(ui_shipyard_item_);

	shipyard_ = Cast<Ashipyard>(ship_object);
	shipyard_->event_build.AddDynamic(this, &UUshipyard::event_build);

	// auto data = ship_object_data::get(ship_objects::shipyard);
	// data.description;

	try {
		auto res = ndb::query<dbs::library>() << (library.atom);
		UE_LOG(LogTemp, Warning, TEXT("error %d"), res.size());
		for (auto item : res)
		{
			auto test = CreateWidget<UUshipyard_item>(GetWorld(), ui_shipyard_item_);
			std::string info;
			info += "\nname : " + item[library.atom.name];
			info += "\nbuild time : " + std::to_string(item[library.atom.stability]);
			test->description_set(info.c_str());
			objects_->AddChild(test);
		}
	}
	catch (const std::exception& e)
	{
		FString zeta(ANSI_TO_TCHAR(e.what()));
		UE_LOG(LogTemp, Warning, TEXT("error %s"), *zeta);
	}
	
	int i = 0;
	for (auto object : neb::ship_object::get())
	{
		// info
		ship_object_build_ = CreateWidget<UUshipyard_item>(GetWorld(), ui_shipyard_item_);
		std::string info;
		info += "\nname : " + object.name;
		info += "\nbuild time : " + std::to_string(object.build_time);

		// build button
		auto button = CreateWidget<UUbutton>(GetWorld(), ui_button_);
		button->text()->SetText(FText::FromString("Build"));
		button->on_click([i, object, this]()
		{
			Cast<Aplayer_controller>(GetOwningPlayer())->log(FString(object.name.c_str()));
			shipyard_->server_build(object.id);
			build_object_ = object;
			build_index_ = i;
		});
		ship_object_build_->action_set(button);

		ship_object_build_->description_set(info.c_str());
		objects_->AddChild(ship_object_build_);
		i++;
	}

}

void UUshipyard::event_build(Eship_object_type build_object, FDateTime date)
{
	UE_LOG(LogTemp, Warning, TEXT("remaining %s"), *date.ToString());
	build_object_ = neb::ship_object::get(build_object);
	build_complete_date_ = date;
	building_ = true;
	UE_LOG(LogTemp, Warning, TEXT("build_object_ %d"), build_object_.build_time);
}

void UUshipyard::NativeTick(const FGeometry& MyGeometry, float DeltaTime)
{
	Super::NativeTick(MyGeometry, DeltaTime);

	if (building_)
	{
		auto build_time = build_object_.build_time;
		auto remaining = (build_complete_date_ - FDateTime::Now()).GetTotalSeconds();
		if (remaining > 0)
		{
			auto percent = (build_time - remaining) / build_time;

			for (int i = 0; i != objects_->GetChildrenCount(); i++)
			{
				if (build_index_ == i)
				{
					Cast<UUshipyard_item>(objects_->GetChildAt(i))->build_progress()->SetPercent(percent);
				}
			}

			//UE_LOG(LogTemp, Warning, TEXT("percent %s"), build_object_.name.c_str());
			//UE_LOG(LogTemp, Warning, TEXT("percent %f"), percent);
		}
	}
}