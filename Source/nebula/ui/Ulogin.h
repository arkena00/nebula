// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ui/Ubutton.h"
#include "Components/NamedSlot.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"

#include "Ulogin.generated.h"

/**
 * 
 */
UCLASS()
class NEBULA_API UUlogin : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual bool Initialize() override;

	//void status_set(FString);
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Nebula")
		TSubclassOf<UUbutton> ui_button_ = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UEditableTextBox* name_ = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UEditableTextBox* pass_ = nullptr;
	
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UNamedSlot* slot_connect_ = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* status_ = nullptr;

	UFUNCTION(BlueprintCallable, Category = "Nebula")
		void connect(FString user, FString pass);
};
