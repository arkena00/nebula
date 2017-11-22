// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/WidgetSwitcher.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/CanvasPanel.h"
#include "Runtime/UMG/Public/Components/CanvasPanelSlot.h"
#include "Runtime/UMG/Public/Components/NamedSlot.h"
#include "Runtime/UMG/Public/Components/HorizontalBox.h"

#include "ui/nbutton.h"
#include "main.generated.h"

UCLASS()
class NEBULA_API Umain : public UUserWidget
{
	GENERATED_BODY()

	virtual bool Initialize() override;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "btn")
		TSubclassOf<Unbutton> bp_button_;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UCanvasPanel* panel_ = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UHorizontalBox* box_menu_ = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UWidgetSwitcher* stack_menu_ = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UNamedSlot* slot_quit_ = nullptr;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* text_info_ = nullptr;

public:
	UTextBlock* info();
};
