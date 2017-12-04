// Fill out your copyright notice in the Description page of Project Settings.

#include "player_controller.h"
#include "player_state.h"
#include "utility/http.h"
#include "ui/nhud.h"
#include "ui/login.h"
#include "ui/main.h"
#include "log.h"
#include "world/ship.h"

#include "UnrealNetwork.h"

void Aplayer_controller::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(Aplayer_controller, player_state);
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
	}
}


void Aplayer_controller::control(Aship* ship)
{
	Possess(ship);
	SetViewTarget(ship);
	client_on_control(ship);
}

void Aplayer_controller::control(int ship_id)
{
	if (ships_.IsValidIndex(ship_id)) control(ships_[ship_id]);
}

void Aplayer_controller::server_control_Implementation(int ship_id)
{
	control(ships_[ship_id]);
}
bool Aplayer_controller::server_control_Validate(int ship_id) { return true; }

void Aplayer_controller::server_test_Implementation(int ship_id)
{
	Aship* a1 = GetWorld()->SpawnActor<Aship>(FVector(20000, 20000, 0), FRotator{ 0, 0, 0 });
	ships_.Add(a1);
}
bool Aplayer_controller::server_test_Validate(int ship_id) { return true; }

void Aplayer_controller::client_on_control_Implementation(Aship* p)
{
	if (GetHUD()) Cast<Anhud>(GetHUD())->ship_ui();
	else nb_error("error");
}

void Aplayer_controller::client_on_ships_update_Implementation()
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
}

void Aplayer_controller::input_test()
{
	if (ships_.IsValidIndex(1))
	{
		server_test(1);
	}
}

void Aplayer_controller::on_connect()
{
	nb_log("connected");
	//Cast<Anhud>(GetHUD())->mode_game();
}

void Aplayer_controller::ship_add(Aship* ship)
{
	ships_.Add(ship);
}

void Aplayer_controller::on_ships_update()
{
	client_on_ships_update();
}

Anhud* Aplayer_controller::nhud()
{
	Anhud* hud = Cast<Anhud>(GetHUD());
	if (!hud) nb_log("hud not found");
	return hud;
}