// Fill out your copyright notice in the Description page of Project Settings.

#include "game/game_instance.h"

#include "database.hpp"

#include "game.h"
#include "log.h"



Ugame_instance::Ugame_instance(const FObjectInitializer& ObjectInitializer) : UGameInstance(ObjectInitializer)
{

}


void Ugame_instance::Init()
{
	nb_log("init objects");

	auto init = new ndb::initializer<ndb::sqlite>;
	ndb::connect<dbs::library>();

	// id | name | build_time | volume

		//ndb::query<dbs::nebula>() << (object.type == ship_object);


	game_.init(this);
	
	neb::ship_object o;
	o.id = Eship_object_type::reactor_solar;
	o.name = "reactor";
	o.build_time = 30;
	game_.ship_objects.push_back(o);

	o.name = "drill";
	o.id = Eship_object_type::drill;
	o.build_time = 50;
	game_.ship_objects.push_back(o);

	o.name = "scanner";
	o.id = Eship_object_type::scanner;
	o.build_time = 300;
	game_.ship_objects.push_back(o);

	o.name = "propulsion";
	o.id = Eship_object_type::propulsion;
	o.build_time = 500;
	game_.ship_objects.push_back(o);
}

