// Fill out your copyright notice in the Description page of Project Settings.

#include "world/ship.h"
#include "game/player_controller.h"
#include "log.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/TextBlock.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

// Sets default values
Aship::Aship()
{
	auto mesh = ConstructorHelpers::FObjectFinderOptional<UStaticMesh>(TEXT("/Game/nebula/world/station/mesh.mesh")).Get();
	ship_hud_ = ConstructorHelpers::FObjectFinder<UClass>(TEXT("WidgetBlueprint'/Game/nebula/blueprint/ui/bp_ship_bar.bp_ship_bar_C'")).Object;

	USceneComponent* root = CreateDefaultSubobject<USceneComponent>(TEXT("root"));
	RootComponent = root;

	// springarm
	springarm_ = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	springarm_->SetupAttachment(root);
	springarm_->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(0.0f, 0.0f, 0.0f));
	springarm_->TargetArmLength = 5000.f;
	springarm_->bEnableCameraLag = true;
	springarm_->CameraLagSpeed = 3.0f;

	// camera
	UCameraComponent* camera = CreateDefaultSubobject<UCameraComponent>(TEXT("camera"));
	camera->SetupAttachment(springarm_, USpringArmComponent::SocketName);

	// mesh
	UStaticMeshComponent* ship = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	ship->SetupAttachment(root);
	ship->SetStaticMesh(mesh);

	ship_name_ = CreateDefaultSubobject<UWidgetComponent>(TEXT("player_name"));
	ship_name_->SetupAttachment(root);

	bReplicates = true;

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


	// update camera
	springarm_->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(camera_pitch_, camera_yaw_, 0.0f));
}

void Aship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("mouse_wheel_up", IE_Pressed, this, &Aship::zoom_in);
	InputComponent->BindAction("mouse_wheel_down", IE_Pressed, this, &Aship::zoom_out);

	InputComponent->BindAxis("mouse_x", this, &Aship::camera_yaw_update);
	InputComponent->BindAxis("mouse_y", this, &Aship::camera_pitch_update);
}

void Aship::zoom_in()
{
	FVector Orgin;
	FVector BoundsExtent;
	GetActorBounds(false, Orgin, BoundsExtent);
	springarm_->TargetArmLength -= 200;
	springarm_->TargetArmLength = FMath::Clamp(springarm_->TargetArmLength, BoundsExtent.X, 10000.f);
}

void Aship::zoom_out()
{
	springarm_->TargetArmLength += 200;
	springarm_->TargetArmLength = FMath::Clamp(springarm_->TargetArmLength, 0.f, 10000.f);
}

void Aship::camera_yaw_update(float n)
{
	auto pc = Cast<Aplayer_controller>(GetController());

	if (pc->IsInputKeyDown(EKeys::LeftMouseButton))
	{
		camera_yaw_ += n;
	}

}

void Aship::camera_pitch_update(float n)
{
	auto pc = Cast<Aplayer_controller>(GetController());

	if (pc->IsInputKeyDown(EKeys::LeftMouseButton))
	{
		camera_pitch_ += n;
		camera_pitch_ = FMath::Clamp(camera_pitch_, -90.f, 90.f);
	}
}