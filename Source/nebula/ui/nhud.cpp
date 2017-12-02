// Fill out your copyright notice in the Description page of Project Settings.

#include "nhud.h"
#include "log.h"
#include "ui/main.h"
#include "ui/login.h"
#include "game/player_controller.h"


void Anhud::BeginPlay()
{
	bp_check(bp_game_ui_);
	bp_check(bp_ship_ui_);

	Aplayer_controller* pc = Cast<Aplayer_controller>(GetOwningPlayerController());

	game_ui_ = CreateWidget<Umain>(pc->GetWorld(), bp_game_ui_);
	game_ui_->AddToViewport();
}

void Anhud::ship_ui()
{

	Aplayer_controller* pc = Cast<Aplayer_controller>(GetOwningPlayerController());

	ship_ui_ = CreateWidget<UUserWidget>(pc->GetWorld(), bp_ship_ui_);
	ship_ui_->AddToViewport();
}

