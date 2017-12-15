// Fill out your copyright notice in the Description page of Project Settings.

#include "Astar.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
Astar::Astar()
{
	auto root = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	RootComponent = root;

	auto star_mesh_ = ConstructorHelpers::FObjectFinderOptional<UStaticMesh>(TEXT("/Game/nebula/world/star/mesh_star.mesh_star")).Get();
	auto star_mat_ = ConstructorHelpers::FObjectFinderOptional<UMaterial>(TEXT("/Game/nebula/material/star.star")).Get();
	UStaticMeshComponent* star = NewObject<UStaticMeshComponent>(this, TEXT("mesh"));

	star->SetupAttachment(root);
	star->SetStaticMesh(star_mesh_);
	star->SetMaterial(0, star_mat_);

	bReplicates = true;
	bAlwaysRelevant = true;
	SetActorEnableCollision(true);

}

// Called when the game starts or when spawned
void Astar::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Astar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

