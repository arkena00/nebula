// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "game.h"

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "game_instance.generated.h"

UCLASS()
class NEBULA_API Ugame_instance : public UGameInstance
{
	GENERATED_BODY()
	
	Ugame_instance(const FObjectInitializer& ObjectInitializer);

	virtual void Init() override;

private:
	neb::game game_;
};
