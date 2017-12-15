// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ui/Uship_object.h"
#include "Ureactor_solar.generated.h"

/**
 * 
 */
UCLASS()
class NEBULA_API UUreactor_solar : public UUship_object
{
	GENERATED_BODY()
	
public:
	void init(Aship_object*) override
	{
		description_set(FText::FromString("reactor solar"));
	}
	
};
