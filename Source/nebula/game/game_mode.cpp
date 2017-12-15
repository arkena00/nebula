// Fill out your copyright notice in the Description page of Project Settings.
#include "game/game_mode.h"
#include "player_controller.h"

#include "world/Auniverse.h"
#include "world/Astar_system.h"
#include "world/Aship.h"

#include "log.h"
#include "database.hpp"


#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

#include <ndb/initializer.hpp>
#include <ndb/engine.hpp>
#include <ndb/basic_engine.hpp>
#include <ndb/engine/mongo/mongo.hpp>

#include "world/Aship_object.h"

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


		nb_log("spawn star_system");
	//neb::star_system star_system_data;
	//star_system_data.generate();

	auto star_system = Cast<Astar_system>(UGameplayStatics::BeginDeferredActorSpawnFromClass(GetWorld(), Astar_system::StaticClass(), FTransform{}));
	UGameplayStatics::FinishSpawningActor(star_system, FTransform{});


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
	param.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	if (pc->id == 1)
	{
		Aship* a1 = GetWorld()->SpawnActor<Aship>(FVector(0, 0, 0), FRotator{ 0, 0, 0 }, param);
		pc->ship_add(a1);
	}
	else
	{
		Aship* a2 = GetWorld()->SpawnActor<Aship>(FVector(5000, 5000, 0), FRotator{ 0, 0, 0 }, param);
	
		a2->object_add(Aship_object::ship_yard);
		a2->object_add(Aship_object::reactor_solar);

		pc->ship_add(a2);
	}
	
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


		player_list_.Add(pc);
	}

	return init;
}
