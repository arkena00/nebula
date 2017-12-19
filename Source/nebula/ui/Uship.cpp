// Fill out your copyright notice in the Description page of Project Settings.

#include "ui/Uship.h"
#include "ui/Uship_object.h"
#include "ui/ship_object/Ushipyard.h"
#include "ui/Ubutton.h"

#include "world/Aship.h"
#include "world/ship_object/Ashipyard.h"

#include "UObject/ConstructorHelpers.h"
#include "log.h"

UUship::UUship(const FObjectInitializer& init) : Super(init)
{
	ui_ship_object_ = ConstructorHelpers::FObjectFinder<UClass>(TEXT("WidgetBlueprint'/Game/nebula/ui/ui_ship_object.ui_ship_object_C'")).Object;
	ui_shipyard_ = ConstructorHelpers::FObjectFinder<UClass>(TEXT("WidgetBlueprint'/Game/nebula/ui/ui_shipyard.ui_shipyard_C'")).Object;
	ui_button_ = ConstructorHelpers::FObjectFinder<UClass>(TEXT("WidgetBlueprint'/Game/nebula/ui/ui_button.ui_button_C'")).Object;
}

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

	name_->SetText(FText::FromString("Ark Station"));

	objects_update();
}

void UUship::objects_update()
{
	objects_->ClearChildren();

	for (auto object : ship_->objects())
	{
		if (object)
		{
			UUship_object* ui_object = nullptr;

			switch (object->type())
			{
			case Eship_object_type::shipyard:
				ui_object = CreateWidget<UUshipyard>(GetWorld(), ui_shipyard_);
				break;

			default:
				ui_object = CreateWidget<UUship_object>(GetWorld(), ui_ship_object_);
			}

			ui_object->init(object);

			stack_objects_->AddChild(ui_object);
			
			// add object button
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
