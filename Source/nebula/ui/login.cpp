// Fill out your copyright notice in the Description page of Project Settings.

#include "login.h"
#include "game/player_controller.h"
#include "nebula/log.h"
#include "utility/http.h"

#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/UMG/Public/Components/NamedSlot.h"
#include "Runtime/UMG/Public/Components/MultiLineEditableText.h"
#include "UObject/ConstructorHelpers.h"
#include "Runtime/Core/Public/Misc/SecureHash.h"


bool Ulogin::Initialize()
{
	auto init = Super::Initialize();
	
	// connect button
	if (!bp_button_)
	{
		nb_error("bp_button is null");
		return init;
	}
	auto btn = CreateWidget<Unbutton>(GetWorld(), bp_button_);
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
			else status_->SetText(FText::FromString(error));
		});
	});
	
	return init;
}