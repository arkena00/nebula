#pragma once

#include "CoreMinimal.h"
#include "Runtime/Online/HTTP/Public/Http.h"

#include <functional>

namespace neb
{
	class http_request
	{
	public:
		using result_callback = std::function<void(TSharedPtr<FJsonObject>)>;

		http_request();

		void add(FString name, FString value);
		void send(FString url, result_callback fn);

	private:
		FHttpModule* http_;
		TSharedPtr<FJsonObject> json_;
		TSharedRef<IHttpRequest> request_;
		result_callback callback_;
	};
} // neb
