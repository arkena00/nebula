// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/VerticalBox.h"
#include "Components/TextBlock.h"
#include "Components/NamedSlot.h"
#include "Components/WidgetSwitcher.h"
#include "Uship.generated.h"

/**
 * 
 */
UCLASS()
class NEBULA_API UUship : public UUserWidget
{
	GENERATED_BODY()

	virtual bool Initialize() override;
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UUbutton> ui_button;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UUship_object> ui_ship_object;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		TSubclassOf<class UUshipyard> ui_shipyard;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UWidgetSwitcher* stack_objects_ = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UTextBlock* name_ = nullptr;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
		UVerticalBox* objects_ = nullptr;

	UFUNCTION()
		void objects_update();

public:
	UUship(const FObjectInitializer& init);
	void init(class Aship* ship);
	
private:
	Aship* ship_ = nullptr;

	class UClass* ui_button_ = nullptr;
	class UClass* ui_ship_object_ = nullptr;
	class UClass* ui_shipyard_ = nullptr;
};
