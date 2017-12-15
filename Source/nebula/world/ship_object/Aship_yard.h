// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "world/Aship_object.h"
#include "Aship_yard.generated.h"

/**
 * 
 */
UCLASS()
class NEBULA_API Aship_yard : public Aship_object
{
	GENERATED_BODY()
	
	
	FString name() const override { return "ship_yard"; }
	type_code type() const override { return Aship_object::ship_yard; }
	
public:
	Aship_yard();
};
