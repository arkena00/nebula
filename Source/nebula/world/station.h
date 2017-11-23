// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "station.generated.h"

UCLASS()
class NEBULA_API Astation : public APawn
{
	GENERATED_BODY()

public:	
	Astation();

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;
	
private:
	class UClass* station_hud_ = nullptr;
	class UWidgetComponent* station_name_ = nullptr;
};
