// Fill out your copyright notice in the Description page of Project Settings.

#include "player_state.h"

#include "UnrealNetwork.h"

Aplayer_state::Aplayer_state(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	bReplicates = true;
	bAlwaysRelevant = true;
}

void Aplayer_state::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(Aplayer_state, name_);
}


