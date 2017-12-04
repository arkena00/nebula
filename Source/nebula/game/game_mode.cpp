// Fill out your copyright notice in the Description page of Project Settings.
#include "game_mode.h"
#include "player_controller.h"
#include "player_state.h"
#include "world/universe.h"
#include "world/ship.h"
#include "log.h"
#include "database.hpp"

#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"

#include <ndb/initializer.hpp>
#include <ndb/engine.hpp>
#include <ndb/basic_engine.hpp>
#include <ndb/engine/mongo/mongo.hpp>

Agame_mode::Agame_mode()
{
	ndb::initializer<ndb::mongo> init;
	ndb::connect<dbs::alpha>();

	nb_log("ndb init");
}

void Agame_mode::BeginPlay()
{
	Super::BeginPlay();

	nb_log("Agame_mode::BeginPlay()");
	// spawn universe
	//GetWorld()->SpawnActor<Auniverse>();

}

void Agame_mode::PreLogin(const FString & Options, const FString & Address, const FUniqueNetIdRepl & UniqueId, FString & ErrorMessage)
{
	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);

	FString id = UGameplayStatics::ParseOption(Options, TEXT("id"));
	UE_LOG(LogTemp, Warning, TEXT("PreLogin %s"), *id);
}

void Agame_mode::PostLogin(APlayerController* new_player_controller)
{
	Super::PostLogin(new_player_controller);
	UE_LOG(LogTemp, Warning, TEXT("PostLogin"));

	auto pc = Cast<Aplayer_controller>(new_player_controller);

	FActorSpawnParameters param;
	param.bNoFail = true;

	Aship* a1 = GetWorld()->SpawnActor<Aship>(FVector(0, 0, 0), FRotator{ 0, 0, 0 }, param);
	Aship* a2 = GetWorld()->SpawnActor<Aship>(FVector(5000, 5000, 0), FRotator{ 0, 0, 0 }, param);
	pc->ship_add(a1);
	pc->ship_add(a2);

	pc->control(a1);

}

FString Agame_mode::InitNewPlayer(APlayerController* new_player_controller, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal)
{
	FString init = Super::InitNewPlayer(new_player_controller, UniqueId, Options, Portal);

	UE_LOG(LogTemp, Warning, TEXT("InitNewPlayer"));
	if (IsRunningDedicatedServer())
	{
		FString id = UGameplayStatics::ParseOption(Options, TEXT("id"));
		auto pc = Cast<Aplayer_controller>(new_player_controller);

		UE_LOG(LogTemp, Warning, TEXT("InitNewPlayer %s"), *id);

		// create player state
		pc->player_state = GetWorld()->SpawnActor<Aplayer_state>();
		pc->player_state->SetOwner(pc);
		pc->player_state->name_ = "ads00";

		player_list_.Add(pc);
	}

	return init;
}
