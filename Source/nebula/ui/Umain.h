// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetSwitcher.h"
#include "Components/Button.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/NamedSlot.h"
#include "Components/HorizontalBox.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"

#include "Umain.generated.h"

UCLASS()
class NEBULA_API UUmain : public UUserWidget
{
	GENERATED_BODY()

	virtual bool Initialize() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UUbutton> ui_button;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<UUserWidget> ui_ship_item;


	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UHorizontalBox* box_menu_ = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UWidgetSwitcher* stack_menu_ = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UVerticalBox* ships_ = nullptr;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* info_ = nullptr;

public:
	UFUNCTION()
		void info_update(FString data);
	
	UFUNCTION()
		void ships_update();
};
