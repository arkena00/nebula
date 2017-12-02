// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "nhud.generated.h"

/**
 * 
 */
UCLASS()
class NEBULA_API Anhud : public AHUD
{
	GENERATED_BODY()

	virtual void BeginPlay() override;

	class Umain* game_ui_ = nullptr;
	class UUserWidget* ship_ui_ = nullptr;
	
public:
	void ship_ui();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class Umain> bp_game_ui_ = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UUserWidget> bp_ship_ui_ = nullptr;
};
