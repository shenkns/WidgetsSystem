// Copyright shenkns Widgets System Developed With Unreal Engine. All Rights Reserved 2023.

#pragma once

#include "Data/Data.h"

#include "UILayerData.generated.h"

UCLASS()
class WIDGETSSYSTEM_API UUILayerData : public UData
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "UI")
	int ZOrder;
};
