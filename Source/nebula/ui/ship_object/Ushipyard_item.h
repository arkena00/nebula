// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Ushipyard_item.generated.h"

/**
 * 
 */
UCLASS()
class NEBULA_API UUshipyard_item : public UUserWidget
{
	GENERATED_BODY()


protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UTextBlock* info_ = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UNamedSlot* action_ = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UProgressBar* build_progress_ = nullptr;

public:
	UProgressBar* build_progress();

	void action_set(class UUbutton* action);
	void description_set(FString value);
	void description_set(FText value);
};