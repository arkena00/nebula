// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "world/Aship_object.h"
#include "Areactor_solar.generated.h"

/**
 * 
 */
UCLASS()
class NEBULA_API Areactor_solar : public Aship_object
{
	GENERATED_BODY()
	
	virtual int build_time() const { return 20; }
	virtual int eps() const { return 80; }
	
	FString name() const override { return "reactor_solar"; }
	Eship_object_type type() const override { return Eship_object_type::reactor_solar; }
	
public:
	Areactor_solar();
};
