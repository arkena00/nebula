// Fill out your copyright notice in the Description page of Project Settings.

#include "universe.h"
#include "Components/TextRenderComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "star.h"
#include "Engine/World.h"

#define LOCTEXT_NAMESPACE "universe"

// Sets default values
Auniverse::Auniverse()
{
	// Create dummy root scene component
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Dummy0"));
	RootComponent = DummyRoot;

	bReplicates = true;
	bAlwaysRelevant = true;
}

void Auniverse::star_add(float x, float y, float z)
{
	GetWorld()->SpawnActor<Astar>(FVector(x, y, z), FRotator(0, 0, 0));

	UE_LOG(LogTemp, Display, TEXT("star : %f / %f"), x, y);
}

// Called when the game starts or when spawned
void Auniverse::BeginPlay()
{
	Super::BeginPlay();


	float x = 0;
	float y = 0;
	float angle = 0.0f;
	int a = 20000, b = 20000;

	for (float i = 0; i < 10000; i ++)
	{
		angle = 0.3 * i;
		int x = (a + b * angle) * FMath::Cos(angle);
		int y = (a + b * angle) * FMath::Sin(angle);
		int z = FMath::FRandRange(-10000, 10000);

		star_add(x, y, z);
	}
	

	UE_LOG(LogTemp, Display, TEXT("universe begin"));

}

// Called every frame
void Auniverse::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

#undef LOCTEXT_NAMESPACE