// Copyright shenkns Widgets System Developed With Unreal Engine. All Rights Reserved 2023.

#pragma once

#include "Blueprint/UserWidget.h"

#include "UILayout.generated.h"

class UOverlay;
class UUILayerData;

UCLASS()
class WIDGETSSYSTEM_API UUILayout : public UUserWidget
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UOverlay* Root;

private:

	UPROPERTY()
	TMap<UUILayerData*, UOverlay*> Layers;

public:

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ClearLayer(UUILayerData* LayerData);
	
	UFUNCTION(BlueprintCallable, Category = "UI")
	void ClearAllLayers();

	UFUNCTION(BlueprintPure, Category = "UI")
	TMap<UUILayerData*, UOverlay*> GetAllLayers() const { return Layers; }

protected:
	
	virtual void NativePreConstruct() override;
};
