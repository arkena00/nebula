// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "hud_main.generated.h"


UCLASS()
class NEBULA_API Ahud_main : public AHUD
{
	GENERATED_BODY()

		Ahud_main();
	virtual void BeginPlay() override;
	
public:
	void init();

	UFUNCTION()
		void ship_control(class Aship* ship);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nebula")
		TSubclassOf<class UUserWidget> ui_main = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nebula")
		TSubclassOf<class UUserWidget> ui_ship = nullptr;

private:
	class UUmain* ui_main_ = nullptr;
	class UUship* ui_ship_ = nullptr;
};
