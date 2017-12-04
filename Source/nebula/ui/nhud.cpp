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

	ship_ui_ = CreateWidget<UUserWidget>(pc->GetWorld(), bp_ship_ui_);
	ship_ui_->AddToViewport();
	ship_ui_->SetVisibility(ESlateVisibility::Hidden);
}

Umain* Anhud::game_ui()
{
	return game_ui_;
}

void Anhud::ship_ui()
{
	//if (ship_ui_) ship_ui_->SetVisibility(ESlateVisibility::Visible);
	//else nb_error("er");
}

