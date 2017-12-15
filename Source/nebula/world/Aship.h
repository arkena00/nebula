// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "world/Aship_object.h"
#include "Aship.generated.h"

UCLASS()
class NEBULA_API Aship : public APawn
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(Fevent_objects_update);

public:	
	Aship();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	// event
	UPROPERTY(BlueprintAssignable)
		Fevent_objects_update event_objects_update;

	// data
	UFUNCTION(BlueprintPure, Category = "Nebula")
		TArray<class Aship_object*> objects();

	// server
	UFUNCTION(Server, Unreliable, WithValidation)
		void server_move_forward();
	UFUNCTION(Server, Unreliable, WithValidation)
		void server_move_forward_stop();
	UFUNCTION(Server, Unreliable, WithValidation)
		void server_move_direction(FRotator rotator);

	void object_add(Aship_object::type_code);

protected:
	virtual void BeginPlay() override;

	// control
	void move_forward();
	void move_forward_stop();
	void move_left();
	void move_right();

	// camera
	void zoom_in();
	void zoom_out();
	void camera_yaw_update(float n);
	void camera_pitch_update(float n);
	void move_x(float n);
	void move_y(float n);
	
private:
	// data
	// event
	// replicatation
	UFUNCTION()
		void client_on_objects_update();


	UPROPERTY(ReplicatedUsing = client_on_objects_update)
		TArray<class Aship_object*> objects_;

	// component
	class UClass* ship_hud_ = nullptr;
	class UWidgetComponent* ship_name_ = nullptr;
	class USpringArmComponent* springarm_ = nullptr;
	class UPawnMovementComponent* movement_ = nullptr;

	// 
	UPROPERTY()
		bool move_forward_ = false;

	// camera
	float camera_pitch_ = 0;
	float camera_yaw_ = 0;
};

