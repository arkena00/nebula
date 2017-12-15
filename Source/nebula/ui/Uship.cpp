// Fill out your copyright notice in the Description page of Project Settings.

#include "ui/Uship.h"
#include "ui/Uship_object.h"
#include "ui/ship_object/Uship_yard.h"
#include "ui/Ubutton.h"

#include "world/Aship.h"
#include "world/ship_object/Aship_yard.h"

#include "log.h"

bool UUship::Initialize()
{
	auto status = Super::Initialize();

	return status;
}

void UUship::init(Aship* ship)
{
	bp_check(ui_button);

	ship_ = ship;

	// bind event_objects_update
	ship->event_objects_update.AddDynamic(this, &UUship::objects_update);

	name_->SetText(FText::FromString("The Setsunaf"));

	objects_update();
}

void UUship::objects_update()
{
	bp_check(ui_button);
	bp_check(ui_ship_object);
	bp_check(ui_ship_yard);

	objects_->ClearChildren();

	for (auto object : ship_->objects())
	{
		if (object)
		{
			UUship_object* ui_object = nullptr;

			switch (object->type())
			{
			case Aship_object::ship_yard:
				ui_object = CreateWidget<UUship_yard>(GetWorld(), ui_ship_yard);
				break;

			default:
				ui_object = CreateWidget<UUship_object>(GetWorld(), ui_ship_object);
			}

			ui_object->init(object);


			stack_objects_->AddChild(ui_object);
			
			auto btn = CreateWidget<UUbutton>(GetWorld(), ui_button);
			btn->on_click([ui_object, this]()
			{
				stack_objects_->SetActiveWidget(ui_object);
			});
			btn->text()->SetText(FText::FromString(object->name()));
			objects_->AddChild(btn);
		}
	}
}
