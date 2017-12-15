// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Auniverse.generated.h"

UCLASS()
class NEBULA_API Auniverse : public AActor
{
	GENERATED_BODY()

		UStaticMesh* star_mesh_;

		class USceneComponent* DummyRoot;

		class UTextRenderComponent* ScoreText;

		class UStaticMeshComponent* BlockMesh;

		void star_add(float x, float y, float z);
	
public:	
	// Sets default values for this actor's properties
	Auniverse();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
