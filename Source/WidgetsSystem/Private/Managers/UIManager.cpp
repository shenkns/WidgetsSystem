// Copyright shenkns Widgets System Developed With Unreal Engine. All Rights Reserved 2023.

#include "Managers/UIManager.h"

#include "Check.h"
#include "ManagersSystem.h"
#include "Blueprint/UserWidget.h"
#include "Module/WidgetsSystemSettings.h"
#include "Widgets/UILayout.h"

void UUIManager::InitManager()
{
	Super::InitManager();

	CreateUILayout();
}

void UUIManager::CreateUILayout()
{
	const UWidgetsSystemSettings* Settings = GetDefault<UWidgetsSystemSettings>();
	CHECK_RETURN(Settings);
	
	if(!ensureAlways(Settings->UILayoutWidgetClass))
	{
		return;
	}
	if(!IsValid(RootLayout))
	{
		RootLayout = CreateWidget<UUILayout>(GetManagerSystem()->GetGameInstance(), Settings->UILayoutWidgetClass);
	}
	if(!RootLayout->IsInViewport())
	{
		RootLayout->ClearAllLayers();
		RootLayout->AddToViewport();
	}
}
