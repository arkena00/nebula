// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "player_state.generated.h"

/**
 * 
 */
UCLASS()
class NEBULA_API Aplayer_state : public AActor
{
	GENERATED_BODY()

	Aplayer_state(const FObjectInitializer& ObjectInitializer);

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
public:
	
	UPROPERTY(Replicated)
		FString name_;
};
