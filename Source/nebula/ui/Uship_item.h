// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Uship_item.generated.h"


UCLASS()
class NEBULA_API UUship_item : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		class UUbutton* button_ = nullptr;
	
};
