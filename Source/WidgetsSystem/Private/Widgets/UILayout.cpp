// Copyright shenkns Widgets System Developed With Unreal Engine. All Rights Reserved 2023.

#include "Widgets/UILayout.h"

#include "Check.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"
#include "Data/UILayerData.h"
#include "Module/WidgetsSystemSettings.h"

void UUILayout::ClearAllLayers()
{
	
}

void UUILayout::NativePreConstruct()
{
	Super::NativePreConstruct();

	Root = WidgetTree->ConstructWidget<UOverlay>(UOverlay::StaticClass(), FName("RootLayout"));
	WidgetTree->RootWidget = Root;

	const UWidgetsSystemSettings* Settings = GetDefault<UWidgetsSystemSettings>();
	CHECK_RETURN(Settings);

	for(const TSoftObjectPtr<UUILayerData>& SoftLayer : Settings->UILayers)
	{
		CHECK_CONTINUE(SoftLayer);
		
		UOverlay* LayerOverlay = WidgetTree->ConstructWidget<UOverlay>(UOverlay::StaticClass(), SoftLayer.LoadSynchronous()->Tag);
		CHECK_CONTINUE(LayerOverlay);

		Layers.Add(SoftLayer.LoadSynchronous(), LayerOverlay);
		
		UOverlaySlot* OverlaySlot = Root->AddChildToOverlay(LayerOverlay);
		CHECK_CONTINUE(OverlaySlot);
		
		OverlaySlot->SetVerticalAlignment(VAlign_Fill);
		OverlaySlot->SetHorizontalAlignment(HAlign_Fill);
	}
}
