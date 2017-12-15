// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Astar_system.generated.h"

UCLASS()
class NEBULA_API Astar_system : public AActor
{
	GENERATED_BODY()
	
public:	
	Astar_system();


protected:
	virtual void BeginPlay() override;

private:

	class Astar* star_;
	TArray<class Aplanet*> planets_;
	
};