#pragma once

#define NXS_STRINGIFY(x) #x
#define NXS_TOSTRING(x) NXS_STRINGIFY(x)
#define NB_LINE __FILE__ ":" NXS_TOSTRING(__LINE__)

#define nb_error(message) UE_LOG(LogTemp, Warning, TEXT(message)); UE_LOG(LogTemp, Warning, TEXT(NB_LINE))
#define nb_log(message) UE_LOG(LogTemp, Warning, TEXT(message))

#define bp_check(pointer) if (pointer == nullptr) { UE_LOG(LogTemp, Error, TEXT("bp pointer missing")); UE_LOG(LogTemp, Error, TEXT(NB_LINE)); return; }