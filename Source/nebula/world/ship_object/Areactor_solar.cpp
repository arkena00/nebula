// Fill out your copyright notice in the Description page of Project Settings.

#include "Areactor_solar.h"

Areactor_solar::Areactor_solar()
{
	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	RootComponent = root;

	bReplicates = true;
}


