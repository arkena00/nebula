// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "player_controller.generated.h"

UCLASS()
class NEBULA_API Aplayer_controller : public APlayerController
{
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(Fevent_ships_update);

	GENERATED_BODY()

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:
	UFUNCTION(Server, reliable, WithValidation)
		void server_test(int ship_id);

	UFUNCTION(Server, reliable, WithValidation, BlueprintCallable)
		void server_control(int ship_id);

	UFUNCTION(Client, reliable)
		void client_on_control(Aship* ship);

	UFUNCTION(Client, reliable)
		void client_on_ships_update();

	UFUNCTION()
		void on_connect();

	Fevent_ships_update event_ships_update;

	class Anhud* nhud();

	// input
	void input_test();

	// action
	void control(class Aship*);
	void control(int ship_id);

	void ship_add(class Aship*);

	UFUNCTION()
		void on_ships_update();

	// BP
	UPROPERTY(Replicated)
		class Aplayer_state* player_state = nullptr;

public:
	UPROPERTY(ReplicatedUsing = on_ships_update)
	TArray<class Aship*> ships_;
};