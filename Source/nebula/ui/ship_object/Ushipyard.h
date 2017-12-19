// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ui/Uship_object.h"
#include "Components/VerticalBox.h"
#include "Ushipyard.generated.h"

/**
 * 
 */
UCLASS()
class NEBULA_API UUshipyard : public UUship_object
{
	GENERATED_BODY()

	virtual void NativeTick(const FGeometry& MyGeometry, float DeltaTime) override;

public:
	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UVerticalBox* objects_ = nullptr;
	
public:
	UUshipyard();
	void init(Aship_object*) override;
	
private:
	UFUNCTION()
		void event_build(Eship_object_type build_object, FDateTime date);

	bool building_ = false;
	int build_index_ = 0;
	FDateTime build_complete_date_;
	neb::ship_object build_object_;

	class Ashipyard* shipyard_ = nullptr;
	class UUshipyard_item* ship_object_build_ = nullptr;
	// ui
	class UClass* ui_button_ = nullptr;
	class UClass* ui_shipyard_item_ = nullptr;
};
