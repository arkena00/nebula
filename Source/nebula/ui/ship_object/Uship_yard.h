// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ui/Uship_object.h"
#include "Components/VerticalBox.h"
#include "Uship_yard.generated.h"

/**
 * 
 */
UCLASS()
class NEBULA_API UUship_yard : public UUship_object
{
	GENERATED_BODY()

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UVerticalBox* objects_ = nullptr;
	
public:
	UUship_yard();
	void init(Aship_object*) override;
	
private:
	class UClass* ui_button_ = nullptr;
	class UClass* ui_ship_object_ = nullptr;
};
