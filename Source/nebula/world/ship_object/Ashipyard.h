// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "world/Aship_object.h"
#include "game.h"


#include "Ashipyard.generated.h"

/**
 * 
 */
UCLASS()
class NEBULA_API Ashipyard : public Aship_object
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(Fevent_build, Eship_object_type, build_object, FDateTime, build_complete_date);

	virtual void Tick(float DeltaTime) override;
public:
	UPROPERTY(BlueprintAssignable)
		Fevent_build event_build;

public:
	UFUNCTION(Server, reliable, WithValidation, BlueprintCallable, Category = "Nebula")
		void server_build(Eship_object_type type_code);

	UFUNCTION(Client, reliable)
		void client_build(Eship_object_type build_object, int64 date);
	
	FString name() const override { return "shipyard"; }
	Eship_object_type type() const override { return Eship_object_type::shipyard; }
	
private:
	Ashipyard();

	FDateTime build_complete_date_;
	neb::ship_object build_object_;
};
