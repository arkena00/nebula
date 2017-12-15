// Fill out your copyright notice in the Description page of Project Settings.

#include "game/game_instance.h"
#include "log.h"

#include "game.h"



Ugame_instance::Ugame_instance(const FObjectInitializer& ObjectInitializer) : UGameInstance(ObjectInitializer)
{

}

void Ugame_instance::Init()
{
	nb_log("init objects");

	game_.init(this);

	neb::ship_object o;
	o.name = "reactor";
	o.build_time = 30;
	game_.ship_objects.push_back(o);

	o.name = "drill";
	o.build_time = 50;
	game_.ship_objects.push_back(o);

	o.name = "scanner";
	o.build_time = 300;
	game_.ship_objects.push_back(o);

	o.name = "propulsion";
	o.build_time = 500;
	game_.ship_objects.push_back(o);
}

