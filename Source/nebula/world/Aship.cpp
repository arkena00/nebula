// Fill out your copyright notice in the Description page of Project Settings.

#include "world/Aship.h"
#include "game/player_controller.h"
#include "world/ship_object/Ashipyard.h"
#include "world/ship_object/Areactor_solar.h"
#include "log.h"

#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/TextBlock.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

#include "UnrealNetwork.h"

// Sets default values
Aship::Aship()
{
	auto mesh = ConstructorHelpers::FObjectFinderOptional<UStaticMesh>(TEXT("/Game/nebula/world/station/mesh.mesh")).Get();
	ship_hud_ = ConstructorHelpers::FObjectFinder<UClass>(TEXT("WidgetBlueprint'/Game/nebula/blueprint/ui/bp_ship_bar.bp_ship_bar_C'")).Object;

	//RootComponent = root;

	// mesh
	UStaticMeshComponent* ship = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mesh"));
	ship->SetStaticMesh(mesh);

	RootComponent = ship;

	// springarm
	springarm_ = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraSpringArm"));
	springarm_->SetupAttachment(RootComponent);
	springarm_->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(-20, 0.0f, 0.0f));
	springarm_->TargetArmLength = 5000.f;
	springarm_->bEnableCameraLag = true;
	springarm_->CameraLagSpeed = 30.0f;

	// camera
	UCameraComponent* camera = CreateDefaultSubobject<UCameraComponent>(TEXT("camera"));
	camera->SetupAttachment(springarm_, USpringArmComponent::SocketName);

	ship_name_ = CreateDefaultSubobject<UWidgetComponent>(TEXT("player_name"));
	ship_name_->SetupAttachment(RootComponent);

	bReplicates = true;
	bReplicateMovement = true;

	SetActorEnableCollision(true);

	bAlwaysRelevant = true;
}

void Aship::BeginPlay()
{
	Super::BeginPlay();

	UUserWidget* text = CreateWidget<UUserWidget>(GetWorld(), ship_hud_);
	ship_name_->SetWidget(text);
	ship_name_->SetWidgetSpace(EWidgetSpace::Screen);
}

void Aship::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (move_forward_)
	{
		FVector location = GetActorLocation();
		location += GetActorForwardVector() * 150;
		SetActorLocation(location);

		UE_LOG(LogTemp, Warning, TEXT("loc %f, %f, %f"), location.X, location.Y, location.Z);
	}

	// update camera
	springarm_->SetRelativeLocationAndRotation(FVector(0.0f, 0.0f, 0.0f), FRotator(camera_pitch_, camera_yaw_, 0.0f));
}

void Aship::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(Aship, objects_);
	//DOREPLIFETIME_CONDITION(Aship, objects_, COND_OwnerOnly);
}

void Aship::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	InputComponent->BindAction("z", IE_Pressed, this, &Aship::move_forward);
	InputComponent->BindAction("z", IE_Released, this, &Aship::move_forward_stop);
	InputComponent->BindAction("q", IE_Pressed, this, &Aship::move_left);
	InputComponent->BindAction("d", IE_Pressed, this, &Aship::move_right);
	
	InputComponent->BindAction("mouse_wheel_up", IE_Pressed, this, &Aship::zoom_in);
	InputComponent->BindAction("mouse_wheel_down", IE_Pressed, this, &Aship::zoom_out);

	InputComponent->BindAxis("mouse_x", this, &Aship::camera_yaw_update);
	InputComponent->BindAxis("mouse_y", this, &Aship::camera_pitch_update);

	InputComponent->BindAxis("mouse_x", this, &Aship::move_x);
	InputComponent->BindAxis("mouse_y", this, &Aship::move_y);
}

void Aship::move_forward()
{
	nb_log("move_forward");
	move_forward_ = true;
	server_move_forward();
}

void Aship::move_forward_stop()
{
	move_forward_ = false;
	server_move_forward_stop();
}

void Aship::server_move_forward_Implementation()
{
	nb_log("server move_forward");
	move_forward_ = true;
}
bool Aship::server_move_forward_Validate() { return true; }

void Aship::server_move_direction_Implementation(FRotator rotation)
{
	RootComponent->SetWorldRotation(rotation);
}
bool Aship::server_move_direction_Validate(FRotator rotation) { return true; }


void Aship::server_move_forward_stop_Implementation()
{
	move_forward_ = false;
}
bool Aship::server_move_forward_stop_Validate() { return true; }

void Aship::move_left()
{
	FRotator rotation = GetActorRotation();
	rotation.Yaw -= 10;
	RootComponent->SetWorldRotation(rotation);
	SetActorRotation(rotation);
	
}

void Aship::move_right()
{
	FRotator rotation = GetActorRotation();
	rotation.Yaw += 10;
	SetActorRotation(rotation);
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

void Aship::move_x(float n)
{
	auto pc = Cast<Aplayer_controller>(GetController());

	if (pc->IsInputKeyDown(EKeys::RightMouseButton))
	{
		camera_yaw_ = 0;
		FRotator rotation = GetActorRotation();
		rotation.Yaw += n;
		server_move_direction(rotation);
		RootComponent->SetWorldRotation(rotation);
	}
}

void Aship::move_y(float n)
{
	auto pc = Cast<Aplayer_controller>(GetController());

	if (pc->IsInputKeyDown(EKeys::RightMouseButton))
	{
		camera_pitch_ = -20;
		FRotator rotation = GetActorRotation();
		rotation.Pitch += n;
		server_move_direction(rotation);
		RootComponent->SetWorldRotation(rotation);
	}
}

void Aship::object_add(Eship_object_type object_code)
{
	auto comp = NewObject<UChildActorComponent>(this);
	
	switch (object_code)
	{
	case Eship_object_type::shipyard:
		comp->SetChildActorClass(Ashipyard::StaticClass());
		break;

	case Eship_object_type::reactor_solar:
		comp->SetChildActorClass(Areactor_solar::StaticClass());
		break;

	default:
		unimplemented();
	}

	comp->CreateChildActor();
	comp->RegisterComponent();

	Aship_object* o = Cast<Aship_object>(comp->GetChildActor());
	o->SetOwner(this);
	
	objects_.Add(o);
}


TArray<class Aship_object*> Aship::objects()
{
	return objects_;
}

void Aship::client_on_objects_update()
{
	event_objects_update.Broadcast();
}