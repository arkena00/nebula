// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "player_controller.generated.h"

UCLASS()
class NEBULA_API Aplayer_controller : public APlayerController
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	// event
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(Fevent_info_update, FString, data);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(Fevent_ships_update);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(Fevent_ship_control, Aship*, ship);

public:
	UFUNCTION(BlueprintPure, Category = "Nebula")
		TArray<class Aship*> ships() { return ships_; }

	// event
	UPROPERTY(BlueprintAssignable)
		Fevent_info_update event_info_update;

	UPROPERTY(BlueprintAssignable)
		Fevent_ships_update event_ships_update;

	UPROPERTY(BlueprintAssignable)
		Fevent_ship_control event_ship_control;

	// server rpc
	UFUNCTION(Server, reliable, WithValidation)
		void server_test(int ship_id);

	UFUNCTION(Server, reliable, WithValidation, BlueprintCallable, Category = "Nebula")
		void server_ship_control(int ship_id);

	// client rpc
	UFUNCTION(Client, reliable)
		void client_ship_control(Aship* ship);

	// on replicatation
	UFUNCTION()
		void client_on_ships_update();
	
	void log(FString);

	// input
	void input_test();

	// action
	void control(class Aship*);
	void control(int ship_id);

	void ship_add(class Aship*);

	void PawnLeavingGame() override;

public:
	int id = 0;

public:
	UPROPERTY(ReplicatedUsing = client_on_ships_update)
		TArray<class Aship*> ships_;
};