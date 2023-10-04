// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"

#include "WidgetsManagerComponent.generated.h"

class UUserWidget;

USTRUCT(BlueprintType)
struct FWidgetHistory
{
	GENERATED_BODY()

	FWidgetHistory() {}
	FWidgetHistory(UUserWidget* HistoryWidget, int HistoryZOrder) : Widget(HistoryWidget), ZOrder(HistoryZOrder) {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	UUserWidget* Widget;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widget")
	int ZOrder;
};

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
	TArray<FWidgetHistory> WidgetsHistory;

public:

	UFUNCTION(BlueprintCallable, Category = "Widgets", meta = (CompactNodeTitle = "OpenWidget"))
	UUserWidget* OpenWidget(UUserWidget* Widget, bool bHideOld = false, bool bClearHistory = false, int ZOrder = 0);

	UFUNCTION(BlueprintCallable, Category = "Widgets", meta = (DeterminesOutputType = "Class", CompactNodeTitle = "OpenFromClass"))
	UUserWidget* OpenWidgetFromClass(TSubclassOf<UUserWidget> Class, bool bHideOld = false, bool bClearHistory = false, int ZOrder = 0);

	UFUNCTION(BlueprintCallable, Category = "Widgets", meta = (CompactNodeTitle = "Back"))
	UUserWidget* Back();
	
protected:
	
	virtual void BeginPlay() override;
};
