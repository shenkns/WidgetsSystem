// Copyright shenkns Widgets System Developed With Unreal Engine. All Rights Reserved 2023.

#include "Module/WidgetsSystemModule.h"

#if UE_EDITOR
#include "ISettingsModule.h"
#include "Module/WidgetsSystemSettings.h"
#include "Log.h"
#endif
	
IMPLEMENT_MODULE(FWidgetsSystemModule, WidgetsSystem);

WIDGETSSYSTEM_API DEFINE_LOG_CATEGORY(LogWidgetsSystem);

void FWidgetsSystemModule::StartupModule()
{
#if UE_EDITOR
	RegisterSystemSettings();
#endif
}

void FWidgetsSystemModule::ShutdownModule()
{
#if UE_EDITOR
	UnregisterSystemSettings();
#endif
}

#if UE_EDITOR
void FWidgetsSystemModule::RegisterSystemSettings() const
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->RegisterSettings(
			"Project",
			"Plugins",
			"Widgets System",
			FText::FromString(TEXT("Widgets System")),
			FText::FromString(TEXT("Configuration settings for Widgets System")),
			GetMutableDefault<UWidgetsSystemSettings>()
		);

		LOG(Display, "Widgets System Settings Registered");
	}
}

void FWidgetsSystemModule::UnregisterSystemSettings() const
{
	if (ISettingsModule* SettingsModule = FModuleManager::GetModulePtr<ISettingsModule>("Settings"))
	{
		SettingsModule->UnregisterSettings("Project", "Plugins", "Widgets System");

		LOG(Display, "Widgets System Settings Unregistered");
	}
}
#endif
