// Fill out your copyright notice in the Description page of Project Settings.

#include "world/Astar_system.h"

#include "world/Astar.h"

Astar_system::Astar_system()
{
	bReplicates = true;
	bAlwaysRelevant = true;
}

void Astar_system::BeginPlay()
{
	Super::BeginPlay();
	
	/*
	for (auto star : data_.stars)
	{
		UE_LOG(LogTemp, Warning, TEXT("spanw star %d : %d"), star.x, star.y);
		Astar* s = GetWorld()->SpawnActor<Astar>(FVector(star.x, star.y, star.z), FRotator{ 0, 0, 0 });
		s->SetActorScale3D(FVector(5, 5, 5));
	}*/

}
