// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "ship.generated.h"

UCLASS()
class NEBULA_API Aship : public APawn
{
	GENERATED_BODY()

public:	
	Aship();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
	void zoom_in();
	void zoom_out();
	void camera_yaw_update(float n);
	void camera_pitch_update(float n);
	
private:
	class UClass* ship_hud_ = nullptr;
	class UWidgetComponent* ship_name_ = nullptr;

	class USpringArmComponent* springarm_;

	bool moving_x = false;

	float camera_pitch_ = 0;
	float camera_yaw_ = 0;
};

