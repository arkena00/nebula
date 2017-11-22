// Fill out your copyright notice in the Description page of Project Settings.

#include "nhud.h"
#include "log.h"
#include "ui/main.h"
#include "ui/login.h"
#include "game/player_controller.h"


void Anhud::BeginPlay()
{
	bp_check(bp_main_);

	Aplayer_controller* pc = Cast<Aplayer_controller>(GetOwningPlayerController());

	main_ = CreateWidget<Umain>(pc->GetWorld(), bp_main_);
	main_->AddToViewport();
}
