// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <string>
#include <vector>

class Ugame_instance;

namespace neb
{
	class game;

	struct atom
	{
		int id;
		std::string name;
	};

	struct ship_object
	{
		int id;
		std::string name;
		int build_time;

		static std::vector<ship_object> get();
	};

	class game
	{
	public:
		game() :
			game_instance_{ nullptr }
		{
			instance_ = this;
		}

		void init(Ugame_instance* game_instance)
		{
			game_instance_ = game_instance;
		}

		static game* instance()
		{
			return instance_;
		}

		std::vector<ship_object> ship_objects;
		std::vector<atom> atoms;

	private:
		Ugame_instance* game_instance_;

		static game* instance_;
	};
}
