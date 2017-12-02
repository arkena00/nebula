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
	
private:
	class UClass* ship_hud_ = nullptr;
	class UWidgetComponent* ship_name_ = nullptr;
};

