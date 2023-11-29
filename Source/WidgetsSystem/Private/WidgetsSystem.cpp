// Copyright shenkns Widgets System Developed With Unreal Engine. All Rights Reserved 2023.

#include "WidgetsSystem.h"

#define LOCTEXT_NAMESPACE "FWidgetsSystemModule"

void FWidgetsSystemModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
}

void FWidgetsSystemModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FWidgetsSystemModule, WidgetsSystem)