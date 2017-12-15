// Fill out your copyright notice in the Description page of Project Settings.

#include "game/hud_main.h"
#include "ui/Umain.h"
#include "ui/Ulogin.h"
#include "ui/Uship.h"

#include "game/player_controller.h"

#include "log.h"

Ahud_main::Ahud_main()
{

}

void Ahud_main::BeginPlay()
{
	bp_check(ui_main);
	bp_check(ui_ship);

	Aplayer_controller* pc = Cast<Aplayer_controller>(GetOwningPlayerController());

	// bind event_ship_control
	if (pc) pc->event_ship_control.AddDynamic(this, &Ahud_main::ship_control);

	ui_main_ = CreateWidget<UUmain>(GetWorld(), ui_main);
	ui_main_->AddToViewport();
}

void Ahud_main::ship_control(Aship* ship)
{
	UE_LOG(LogTemp, Warning, TEXT("ship_ui"));
	if (IsValid(ui_ship_)) ui_ship_->RemoveFromViewport();
	ui_ship_ = CreateWidget<UUship>(GetWorld(), ui_ship);
	ui_ship_->init(ship);
	ui_ship_->AddToViewport();
}