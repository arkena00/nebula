// Fill out your copyright notice in the Description page of Project Settings.

#include "game/player_controller.h"

#include "world/Aship.h"
#include "world/Astar.h"

#include "ui/Umain.h"
#include "game/hud_main.h"
#include "ui/Ulogin.h"

#include "utility/http.h"
#include "log.h"

#include "UnrealNetwork.h"

void Aplayer_controller::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(Aplayer_controller, ships_);
}

void Aplayer_controller::BeginPlay()
{
	Super::BeginPlay();

	if (IsRunningDedicatedServer())
	{
		
	}

	if (IsLocalPlayerController())
	{
		nb_log("BeginPlay");
		bShowMouseCursor = true;
		SetInputMode(FInputModeGameAndUI{});

		server_ship_control(0);
	}
}


void Aplayer_controller::control(Aship* ship)
{
	Possess(ship);
	client_ship_control(ship);
}

void Aplayer_controller::control(int ship_id)
{
	if (ships_.IsValidIndex(ship_id)) control(ships_[ship_id]);
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////           SERVER RPC           ////////////////////////
////////////////////////////////////////////////////////////////////////////////
void Aplayer_controller::server_ship_control_Implementation(int ship_id)
{
	control(ships_[ship_id]);
}
bool Aplayer_controller::server_ship_control_Validate(int ship_id) { return true; }

////////////////////////////////////////////////////////////////////////////////
////////////////////////           CLIENT RPC           ////////////////////////
////////////////////////////////////////////////////////////////////////////////
void Aplayer_controller::client_ship_control_Implementation(Aship* ship)
{
	event_ship_control.Broadcast(ship);
}

void Aplayer_controller::client_on_ships_update()
{
	event_ships_update.Broadcast();
}

////////////////////////////////////////////////////////////////////////////////
////////////////////////             INPUT              ////////////////////////
////////////////////////////////////////////////////////////////////////////////

void Aplayer_controller::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("test", IE_Pressed, this, &Aplayer_controller::input_test);
	//InputComponent->BindAction("test2", IE_Pressed, this, &Aplayer_controller::input_test2);
}

void Aplayer_controller::input_test()
{
	server_test(0);
}


void Aplayer_controller::ship_add(Aship* ship)
{
	ships_.Add(ship);
}


void Aplayer_controller::PawnLeavingGame()
{

}


void Aplayer_controller::log(FString data)
{
	event_info_update.Broadcast(data);
}


void Aplayer_controller::server_test_Implementation(int ship_id)
{
	FActorSpawnParameters param;
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
	auto a1 = GetWorld()->SpawnActor<Aship>(FVector(20000, 20000, 0), FRotator{ 0, 0, 0 }, param);
	a1->object_add(Eship_object_type::shipyard);
	nb_log("add ship");
	ships_.Add(a1);
}
bool Aplayer_controller::server_test_Validate(int ship_id) { return true; }