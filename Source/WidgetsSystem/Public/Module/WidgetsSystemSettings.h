// Copyright shenkns Widgets System Developed With Unreal Engine. All Rights Reserved 2023.

#pragma once

#include "UObject/Object.h"

#include "WidgetsSystemSettings.generated.h"

class UUILayerData;

UCLASS(Config=Game, DefaultConfig)
class WIDGETSSYSTEM_API UWidgetsSystemSettings : public UObject
{
	GENERATED_BODY()

public:

	UPROPERTY(Config, EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	TArray<TSoftObjectPtr<UUILayerData>> UILayers;
};
