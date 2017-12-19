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
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UHorizontalBox* box_menu_ = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UWidgetSwitcher* stack_menu_ = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UVerticalBox* ships_ = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UNamedSlot* ship_ = nullptr;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* info_ = nullptr;

public:
	UUmain(const FObjectInitializer& init);

	void ui_ship_set(class UUship*);

	UFUNCTION()
		void info_update(FString data);

	UFUNCTION()
		void ships_update();

private:
	// ui
	class UClass* ui_button_ = nullptr;
	class UClass* ui_ship_item_ = nullptr;
};
