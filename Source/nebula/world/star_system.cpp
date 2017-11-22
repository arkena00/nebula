// Fill out your copyright notice in the Description page of Project Settings.

#include "star_system.h"


// Sets default values
Astar_system::Astar_system()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Astar_system::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Astar_system::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

