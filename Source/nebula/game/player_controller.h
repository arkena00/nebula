// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "player_controller.generated.h"

UCLASS()
class NEBULA_API Aplayer_controller : public APlayerController
{
	GENERATED_BODY()

	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

public:
	// BP
	UPROPERTY(Replicated)
		class Aplayer_state* player_state = nullptr;

	UFUNCTION(Server, reliable, WithValidation)
		void server_control(int ship_id);

	UFUNCTION(Client, reliable)
		void client_on_control(Aship* ship);

	UFUNCTION()
		void on_connect();

	// input
	void input_test();

	// action
	void control(class Aship*);

	void ship_add(class Aship*);

private:
	UPROPERTY(Replicated)
	TArray<class Aship*> ship_list_;
};