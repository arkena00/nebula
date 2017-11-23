// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "player_controller.generated.h"


/**
 * 
 */
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

	UPROPERTY(ReplicatedUsing = on_connect)
		bool connected = false;

	UFUNCTION(Client, reliable)
		void test();

	UFUNCTION()
		void on_connect();

	// input
	void input_test();
};