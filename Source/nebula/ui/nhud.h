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

	class Umain* main_ = nullptr;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class Umain> bp_main_ = nullptr;
};
