// Copyright shenkns Widgets System Developed With Unreal Engine. All Rights Reserved 2023.

#pragma once

#include "Managers/Manager.h"

#include "UIManager.generated.h"

class UUILayout;

UCLASS()
class WIDGETSSYSTEM_API UUIManager : public UManager
{
	GENERATED_BODY()

private:

	UPROPERTY()
	UUILayout* RootLayout;

public:

	virtual void InitManager() override;

	UFUNCTION(BlueprintPure, Category = "UI")
	UUILayout* GetUILayout() const { return RootLayout; }

	UFUNCTION(BlueprintCallable, Category = "UI")
	void CreateUILayout();
};
