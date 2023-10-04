// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/ActorComponent.h"

#include "WidgetsManagerComponent.generated.h"

class UUserWidget;

UENUM(BlueprintType)
enum EWidgetOpenMethod
{
	Simple,
	HidePrevious,
	HideAll,
	ClearHistory
};

USTRUCT(BlueprintType)
struct WIDGETSSYSTEM_API FWidgetHistory
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

	UPROPERTY(VisibleInstanceOnly, Category = "Widgets")
	TArray<FWidgetHistory> WidgetsHistory;

	bool PlayingTransition;

public:

	// Widgets management
	UFUNCTION(BlueprintCallable, Category = "WidgetsSystem", meta = (CompactNodeTitle = "OpenWidget"))
	UUserWidget* OpenWidget(UUserWidget* Widget, EWidgetOpenMethod OpenMethod = EWidgetOpenMethod::Simple, int ZOrder = 0, bool Instant = false);

	UFUNCTION(BlueprintCallable, Category = "WidgetsSystem", meta = (DeterminesOutputType = "Class", CompactNodeTitle = "OpenFromClass"))
	UUserWidget* OpenWidgetFromClass(TSubclassOf<UUserWidget> Class, EWidgetOpenMethod OpenMethod = EWidgetOpenMethod::Simple, int ZOrder = 0, bool Instant = false);

	UFUNCTION(BlueprintCallable, Category = "WidgetsSystem", meta = (CompactNodeTitle = "Back"))
	UUserWidget* Back(bool Instant = false);

	// Getters
	UFUNCTION(BlueprintPure, Category = "WidgetsSystem", meta = (CompactNodeTitle = "CurrentWidget"))
	UUserWidget* GetCurrentWidget() const;

	UFUNCTION(BlueprintPure, Category = "WidgetsSystem", meta = (CompactNodeTitle = Locked))
	bool IsLocked() const;
	
protected:
	
	virtual void BeginPlay() override;
};
