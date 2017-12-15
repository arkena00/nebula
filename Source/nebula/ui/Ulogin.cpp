// Fill out your copyright notice in the Description page of Project Settings.

#include "ui/Ulogin.h"
#include "game/player_controller.h"

#include "utility/http.h"
#include "log.h"

#include "Blueprint/UserWidget.h"
#include "Components/NamedSlot.h"
#include "Components/MultiLineEditableText.h"
#include "UObject/ConstructorHelpers.h"
#include "Misc/SecureHash.h"


bool UUlogin::Initialize()
{
	auto init = Super::Initialize();
	
	bp_check_ret(ui_button_, init);

	auto btn = CreateWidget<UUbutton>(GetWorld(), ui_button_);
	btn->text()->SetText(FText::FromString("Connect"));
	slot_connect_->SetContent(btn);
	
	// connect click
	btn->on_click([this]()
	{
		neb::http_request req;
		req.add("name", name_->GetText().ToString());
		FString p = pass_->GetText().ToString();
		req.add("pass", FMD5::HashAnsiString(*pass_->GetText().ToString()));

		status_->SetText(FText::FromString("connecting..."));

		// send login id to main server
		req.send("http://nebula.neuroshok.com/api/login.php", [this](TSharedPtr<FJsonObject> json)
		{
			int success = json->GetIntegerField("success");
			FString error = json->GetStringField("result");

			if (success)
			{
				int id = json->GetIntegerField("id");
				FString url = "127.0.0.1/lvl_world";
				url += "?id=" + FString::FromInt(id);
				GetOwningPlayer()->ClientTravel(url, ETravelType::TRAVEL_Relative);
			}
			else GetOwningPlayer()->ClientTravel("127.0.0.1/lvl_world?id=999", ETravelType::TRAVEL_Relative);  // status_->SetText(FText::FromString(error));
		});
	});
	
	return init;
}

void UUlogin::connect(FString user, FString pass)
{
	neb::http_request req;
	req.add("name", user);
	FString p = pass_->GetText().ToString();
	req.add("pass", FMD5::HashAnsiString(*pass));

	status_->SetText(FText::FromString("connecting..."));

	// send login id to main server
	req.send("http://nebula.neuroshok.com/api/login.php", [this](TSharedPtr<FJsonObject> json)
	{
		int success = json->GetIntegerField("success");
		FString error = json->GetStringField("result");

		if (success)
		{
			int id = json->GetIntegerField("id");
			FString url = "127.0.0.1/lvl_world";
			url += "?id=" + FString::FromInt(id);
			GetOwningPlayer()->ClientTravel(url, ETravelType::TRAVEL_Relative);
		}
		else GetOwningPlayer()->ClientTravel("127.0.0.1/lvl_world?id=999", ETravelType::TRAVEL_Relative);  // status_->SetText(FText::FromString(error));
	});
}