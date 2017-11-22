// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include <functional>

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/Button.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"

#include "nbutton.generated.h"


/**
 * 
 */
UCLASS()
class NEBULA_API Unbutton : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	virtual bool Initialize() override;

	void on_click(std::function<void()>);

	UFUNCTION()
	void click();

	UTextBlock* text() { return text_; }

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UButton* button_ = nullptr;

	UPROPERTY(BlueprintReadWrite, meta = (BindWidget))
	UTextBlock* text_ = nullptr;

private:

	std::function<void()> on_click_;
};
