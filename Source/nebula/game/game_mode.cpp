// Fill out your copyright notice in the Description page of Project Settings.
#include "game_mode.h"
#include "player_controller.h"
#include "player_state.h"
#include "world/universe.h"
#include "world/station.h"
#include "log.h"

#include "Runtime/Engine/Classes/Engine/World.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"



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

void Agame_mode::PostLogin(APlayerController* new_player)
{
	Super::PostLogin(new_player);

}

FString Agame_mode::InitNewPlayer(APlayerController* new_player_controller, const FUniqueNetIdRepl& UniqueId, const FString& Options, const FString& Portal)
{
	FString init = Super::InitNewPlayer(new_player_controller, UniqueId, Options, Portal);

	if (IsRunningDedicatedServer())
	{
		FString id = UGameplayStatics::ParseOption(Options, TEXT("id"));
		UE_LOG(LogTemp, Warning, TEXT("InitNewPlayer %s"), *id);
		auto pc = Cast<Aplayer_controller>(new_player_controller);

		// create player state
		pc->player_state = GetWorld()->SpawnActor<Aplayer_state>();
		pc->player_state->SetOwner(pc);
		pc->player_state->name_ = "ads00";

		player_list_.Add(pc);

		pc->connected = true;

		//auto station = GetWorld()->SpawnActor<Astation>();
		if (id == "1") { GetWorld()->SpawnActor<Astation>(FVector(0, 0, 0), FRotator{}); }
		else GetWorld()->SpawnActor<Astation>(FVector(10000, 10000, 0), FRotator{});
		//pc->Possess(station);
	}

	return init;
}
