// Fill out your copyright notice in the Description page of Project Settings.

#include "station.h"
#include "log.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/TextBlock.h"

// Sets default values
Astation::Astation()
{
	auto mesh = ConstructorHelpers::FObjectFinderOptional<UStaticMesh>(TEXT("/Game/nebula/world/station/mesh.mesh")).Get();
	station_hud_ = ConstructorHelpers::FObjectFinder<UClass>(TEXT("WidgetBlueprint'/Game/nebula/blueprint/ui/station/bp_station.bp_station_C'")).Object;

	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	RootComponent = root;

	// mesh
	UStaticMeshComponent* station = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	station->SetupAttachment(root);
	station->SetStaticMesh(mesh);

	station_name_ = CreateDefaultSubobject<UWidgetComponent>(TEXT("player_name"));
	station_name_->SetupAttachment(root);

	bReplicates = true;
	bReplicateMovement = true;
	SetActorEnableCollision(false);

	bAlwaysRelevant = true;
}

// Called when the game starts or when spawned
void Astation::BeginPlay()
{
	Super::BeginPlay();

		UUserWidget* text = CreateWidget<UUserWidget>(GetWorld(), station_hud_);
		station_name_->SetWidget(text);
		station_name_->SetWidgetSpace(EWidgetSpace::Screen);
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

