// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Components/NamedSlot.h"

#include "world/Aship_object.h"
#include "ui/Ubutton.h"

#include "Uship_object.generated.h"

/**
 * 
 */
UCLASS()
class NEBULA_API UUship_object : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* info_ = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UNamedSlot* action_ = nullptr;
	
public:
	virtual void init(Aship_object* object)
	{
		FString info;
		info += "Default description";
		info += "\nBuild time : " + FString::FromInt(object->build_time());
		info += "\nEnergy / s : " + FString::FromInt(object->eps());

		description_set(info);
	}

	void action_set(UUbutton* action)
	{
		action_->SetContent(action);
	}

	void description_set(FString value)
	{
		description_set(FText::FromString(value));
	}

	void description_set(FText value)
	{
		if (info_) info_->SetText(value);
	}
};
