// Fill out your copyright notice in the Description page of Project Settings.

#include "station.h"
#include "log.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
Astation::Astation()
{
	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	RootComponent = root;

	UStaticMeshComponent* station = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	station->SetupAttachment(root);

	auto mesh = ConstructorHelpers::FObjectFinderOptional<UStaticMesh>(TEXT("/Game/nebula/model/station/mesh_station.mesh_station")).Get();

	station->SetStaticMesh(mesh);

	SetRemoteRoleForBackwardsCompat(ROLE_SimulatedProxy);
	bReplicates = true;
	bReplicateMovement = true;
	SetActorEnableCollision(false);

	bAlwaysRelevant = true;
}

// Called when the game starts or when spawned
void Astation::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void Astation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator rot = FRotator(0.f, 20.f, 0.f);

	AddActorLocalRotation(rot * DeltaTime);
}

// Called to bind functionality to input
void Astation::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

