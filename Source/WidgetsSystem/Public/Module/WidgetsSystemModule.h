// Copyright shenkns Widgets System Developed With Unreal Engine. All Rights Reserved 2023.

#pragma once

#include "Modules/ModuleManager.h"

WIDGETSSYSTEM_API DECLARE_LOG_CATEGORY_EXTERN(LogWidgetsSystem, Log, All);

class FWidgetsSystemModule : public IModuleInterface
{
public:
	
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

private:

#if UE_EDITOR
	// Init System Configuration
	void RegisterSystemSettings() const;
	void UnregisterSystemSettings() const;
#endif
};
