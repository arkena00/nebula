// Fill out your copyright notice in the Description page of Project Settings.

#include "world/ship.h"
#include "game/player_controller.h"
#include "log.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/TextBlock.h"

// Sets default values
Aship::Aship()
{
	auto mesh = ConstructorHelpers::FObjectFinderOptional<UStaticMesh>(TEXT("/Game/nebula/world/station/mesh.mesh")).Get();
	ship_hud_ = ConstructorHelpers::FObjectFinder<UClass>(TEXT("WidgetBlueprint'/Game/nebula/blueprint/ui/bp_ship_bar.bp_ship_bar_C'")).Object;

	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	RootComponent = root;

	// mesh
	UStaticMeshComponent* ship = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	ship->SetupAttachment(root);
	ship->SetStaticMesh(mesh);

	ship_name_ = CreateDefaultSubobject<UWidgetComponent>(TEXT("player_name"));
	ship_name_->SetupAttachment(root);

	bReplicates = true;
	SetActorEnableCollision(false);

	bAlwaysRelevant = true;
}

// Called when the game starts or when spawned
void Aship::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* text = CreateWidget<UUserWidget>(GetWorld(), ship_hud_);
	ship_name_->SetWidget(text);
	ship_name_->SetWidgetSpace(EWidgetSpace::Screen);
}

// Called every frame
void Aship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FRotator rot = FRotator(0.f, 20.f, 0.f);

	AddActorLocalRotation(rot * DeltaTime);
}

// Called to bind functionality to input
void Aship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
