// Fill out your copyright notice in the Description page of Project Settings.

#include "game.h"

namespace neb
{
	game* game::instance_ = nullptr;

	std::vector<ship_object> ship_object::get()
	{
		return game::instance()->ship_objects;
	}
}