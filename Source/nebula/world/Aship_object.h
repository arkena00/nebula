// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Aship_object.generated.h"

UCLASS(abstract)
class NEBULA_API Aship_object : public AActor
{
	GENERATED_BODY()
	
public:	
	Aship_object();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	enum type_code
	{
		ship_yard,
		reactor_solar
	};


	virtual void Tick(float DeltaTime) override;

	// default value
	virtual int build_time() const { return 60; }
	virtual int eps() const { return 0; }

	virtual FString name() const PURE_VIRTUAL(Aship_object::name, return "";);
	virtual type_code type() const PURE_VIRTUAL(Aship_object::type, return ship_yard;);
};
