// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "WidgetSystemLibrary.generated.h"

class UWidgetManagerComponent;

UCLASS()
class WIDGETSYSTEM_API UWidgetSystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "Widgets", meta = (CompactNodeTitle = "WidgetManager"))
	static UWidgetManagerComponent* GetWidgetManager();

	UFUNCTION(BlueprintCallable, Category = "Widgets", meta = (CompactNodeTitle = "OpenWidget"))
	static void OpenWidget(UUserWidget* Widget, bool bHideOld = false, int ZOrder = 0);

	UFUNCTION(BlueprintCallable, Category = "Widgets", meta = (DeterminesOutputType = "Class", CompactNodeTitle = "OpenFromClass"))
	static UUserWidget* OpenWidgetFromClass(TSubclassOf<UUserWidget> Class, bool bHideOld = false, int ZOrder = 0);

	UFUNCTION(BlueprintCallable, Category = "Widgets", meta = (CompactNodeTitle = "Back"))
	static UUserWidget* Back();
};
