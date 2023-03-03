// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"

#include "WidgetsManagerComponent.generated.h"

class UUserWidget;

UCLASS(ClassGroup = (Widgets), meta = (BlueprintSpawnableComponent))
class WIDGETSSYSTEM_API UWidgetsManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	
	UWidgetsManagerComponent();

protected:

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Widgets")
	TSubclassOf<UUserWidget> StartWidgetClass;

	UPROPERTY(BlueprintReadOnly, Category = "Widgets")
	UUserWidget* CurrentWidget;

	UPROPERTY(BlueprintReadOnly, Category = "Widgets")
	TArray<UUserWidget*> Widgets;

public:

	UFUNCTION(BlueprintCallable, Category = "Widgets", meta = (CompactNodeTitle = "OpenWidget"))
	void OpenWidget(UUserWidget* Widget, bool bHideOld = false, int ZOrder = 0);

	UFUNCTION(BlueprintCallable, Category = "Widgets", meta = (DeterminesOutputType = "Class", CompactNodeTitle = "OpenFromClass"))
	UUserWidget* OpenWidgetFromClass(TSubclassOf<UUserWidget> Class, bool bHideOld = false, int ZOrder = 0);

	UFUNCTION(BlueprintCallable, Category = "Widgets", meta = (CompactNodeTitle = "Back"))
	UUserWidget* Back();
	
protected:
	
	virtual void BeginPlay() override;
};
