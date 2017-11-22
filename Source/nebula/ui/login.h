// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ui/nbutton.h"
#include "Runtime/UMG/Public/Components/NamedSlot.h"
#include "Runtime/UMG/Public/Components/TextBlock.h"
#include "Runtime/UMG/Public/Components/EditableTextBox.h"

#include "login.generated.h"

/**
 * 
 */
UCLASS()
class NEBULA_API Ulogin : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	//void status_set(FString);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "ui")
		TSubclassOf<Unbutton> bp_button_ = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UEditableTextBox* name_ = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UEditableTextBox* pass_ = nullptr;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UNamedSlot* slot_connect_ = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* status_ = nullptr;
};
