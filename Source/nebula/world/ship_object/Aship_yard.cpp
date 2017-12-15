// Fill out your copyright notice in the Description page of Project Settings.

#include "Aship_yard.h"

Aship_yard::Aship_yard()
{
	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	RootComponent = root;

	bReplicates = true;
}


