// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "ReWebsocket.h"

#define LOCTEXT_NAMESPACE "FReWebsocketModule"

void FReWebsocketModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	if (!FModuleManager::Get().IsModuleLoaded("WebSockets"))
	{
		FModuleManager::Get().LoadModule("WebSockets");
	}
}

void FReWebsocketModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FReWebsocketModule, ReWebsocket)

DEFINE_LOG_CATEGORY(ReWebsocketLog)