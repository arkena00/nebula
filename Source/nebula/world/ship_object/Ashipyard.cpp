// Fill out your copyright notice in the Description page of Project Settings.

#include "Ashipyard.h"

#include "UnrealNetwork.h"

Ashipyard::Ashipyard()
{
	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	RootComponent = root;

	bReplicates = true;
	bAlwaysRelevant = true;
	SetActorTickEnabled(false);
	SetActorTickInterval(1);
}


void Ashipyard::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	auto remaining = build_complete_date_ - FDateTime::Now();
	//auto percent = build_complete_date_.GetTicks() - remaining;
	// build complete
	if (remaining <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("complete"));
		SetActorTickEnabled(false);
	}
	else UE_LOG(LogTemp, Warning, TEXT("remaining %f"), remaining.GetTotalSeconds());
}

void Ashipyard::server_build_Implementation(Eship_object_type type_code)
{
	build_object_ = neb::ship_object::get(type_code);
	auto build_time = build_object_.build_time;
	auto duration = FTimespan::FromSeconds(build_time);

	build_complete_date_ = FDateTime::Now() + duration;
	client_build(build_object_.id, build_complete_date_.ToUnixTimestamp());


	SetActorTickEnabled(true);

}
bool Ashipyard::server_build_Validate(Eship_object_type type_code)
{
	return true;
}

void Ashipyard::client_build_Implementation(Eship_object_type build_object, int64 date)
{
	event_build.Broadcast(build_object, FDateTime::FromUnixTimestamp(date));
}