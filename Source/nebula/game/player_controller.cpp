// Fill out your copyright notice in the Description page of Project Settings.

#include "player_controller.h"
#include "player_state.h"
#include "utility/http.h"
#include "ui/nhud.h"
#include "ui/login.h"
#include "ui/main.h"
#include "log.h"
#include "world/station.h"

#include "UnrealNetwork.h"


void Aplayer_controller::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(Aplayer_controller, connected);
	DOREPLIFETIME(Aplayer_controller, player_state);
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
		//if (connected) Cast<Anhud>(GetHUD())->mode_game();
	}
}

void Aplayer_controller::test_Implementation()
{
	nb_log("test impl");
}

void Aplayer_controller::SetupInputComponent()
{
	Super::SetupInputComponent();
	InputComponent->BindAction("test", IE_Pressed, this, &Aplayer_controller::input_test);
}

void Aplayer_controller::input_test()
{
	nb_log("SpawnActor");
	Astation* station = GetWorld()->SpawnActor<Astation>(Astation::StaticClass(), FVector(100, 100, 100), FRotator(0, 0, 0));
}

void Aplayer_controller::on_connect()
{
	nb_log("connected");
	//Cast<Anhud>(GetHUD())->mode_game();
}