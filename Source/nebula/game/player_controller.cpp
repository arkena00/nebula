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
	DOREPLIFETIME(Aplayer_controller, ship_list_);
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


void Aplayer_controller::server_control_Implementation(int ship_id)
{
	control(ship_list_[ship_id]);
}

bool Aplayer_controller::server_control_Validate(int ship_id)
{
	return true;
}

void Aplayer_controller::client_on_control_Implementation(Aship* p)
{
	if (GetHUD()) Cast<Anhud>(GetHUD())->ship_ui();
	else nb_error("error");
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
	if (ship_list_.IsValidIndex(0))
	{
		server_control(0);
	}


	//SetViewTarget(GetPawn());
	//Astation* station = GetWorld()->SpawnActor<Astation>(Astation::StaticClass(), FVector(100, 100, 100), FRotator(0, 0, 0));
}

void Aplayer_controller::on_connect()
{
	nb_log("connected");
	//Cast<Anhud>(GetHUD())->mode_game();
}

void Aplayer_controller::ship_add(Aship* ship)
{
	ship_list_.Add(ship);

}