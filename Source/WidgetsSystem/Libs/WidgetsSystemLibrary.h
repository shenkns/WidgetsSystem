// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include "WidgetsSystemLibrary.generated.h"

class UWidgetsManagerComponent;

UCLASS()
class WIDGETSSYSTEM_API UWidgetsSystemLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure, Category = "Widgets", meta = (CompactNodeTitle = "WidgetManager"))
	static UWidgetsManagerComponent* GetWidgetManager();

	UFUNCTION(BlueprintCallable, Category = "Widgets", meta = (CompactNodeTitle = "OpenWidget"))
	static UUserWidget* OpenWidget(UUserWidget* Widget, bool bHideOld = false, int ZOrder = 0);

	UFUNCTION(BlueprintCallable, Category = "Widgets", meta = (DeterminesOutputType = "Class", CompactNodeTitle = "OpenFromClass"))
	static UUserWidget* OpenWidgetFromClass(TSubclassOf<UUserWidget> Class, bool bHideOld = false, int ZOrder = 0);

	UFUNCTION(BlueprintCallable, Category = "Widgets", meta = (CompactNodeTitle = "Back"))
	static UUserWidget* Back();
};
