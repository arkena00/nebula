// Fill out your copyright notice in the Description page of Project Settings.

#include "http.h"

#include "Runtime/Core/Public/Misc/SecureHash.h"
#include "Runtime/Json/Public/Dom/JsonObject.h"
#include "Runtime/Json/Public/Json.h"

namespace neb
{
	http_request::http_request() : 
		http_(&FHttpModule::Get()),
		json_(MakeShareable(new FJsonObject)),
		request_(http_->CreateRequest())
	{
		request_ = http_->CreateRequest();

		request_->SetVerb("POST");
		request_->SetHeader(TEXT("User-Agent"), "X-UnrealEngine-Agent");
		request_->SetHeader("Content-Type", TEXT("application/json"));
	}

	void http_request::add(FString name, FString value)
	{
		json_->SetStringField(name, value);
	}

	void http_request::send(FString url, result_callback callback)
	{
		FString output;
		TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&output);
		FJsonSerializer::Serialize(json_.ToSharedRef(), Writer);

		request_->SetURL(url);
		request_->SetContentAsString(output);


		request_->OnProcessRequestComplete().BindLambda([callback](FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
		{
			TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(Response->GetContentAsString());
			TSharedPtr<FJsonObject> json_result;

			if (FJsonSerializer::Deserialize(Reader, json_result))
			{
				if (callback) callback(json_result);
			}
		});

		request_->ProcessRequest();
	}
} // neb
