// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/WidgetsManagerComponent.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

UWidgetsManagerComponent::UWidgetsManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

UUserWidget* UWidgetsManagerComponent::OpenWidget(UUserWidget* Widget, bool bHideOld, bool bClearHistory, int ZOrder)
{
	if(bHideOld)
	{
		for(const FWidgetHistory& OldWidget : WidgetsHistory)
		{
			if(OldWidget.Widget)
			{
				OldWidget.Widget->RemoveFromParent();
			}
		}
	}

	if(bClearHistory)
	{
		WidgetsHistory.Empty();
	}

	if(!Widget) return nullptr;

	WidgetsHistory.Add(FWidgetHistory(Widget, ZOrder));
	CurrentWidget = Widget;

	CurrentWidget->AddToViewport(ZOrder);
	
	return CurrentWidget;
}

UUserWidget* UWidgetsManagerComponent::OpenWidgetFromClass(TSubclassOf<UUserWidget> Class, bool bHideOld, bool bClearHistory, int ZOrder)
{
	if(!IsValid(Class)) return nullptr;

	if(UUserWidget* Widget = CreateWidget<UUserWidget, UWorld>(GetWorld(), Class, FName(FGuid::NewGuid().ToString())))
	{
		return OpenWidget(Widget, bHideOld, bClearHistory, ZOrder);
	}

	return nullptr;
}

UUserWidget* UWidgetsManagerComponent::Back()
{
	if(WidgetsHistory.Num() <= 1) return nullptr;

	WidgetsHistory.RemoveAt(WidgetsHistory.Num() - 1);

	if(CurrentWidget)
	{
		CurrentWidget->RemoveFromParent();
	}
	
	CurrentWidget = WidgetsHistory.Last().Widget;
	const int ZOrder = WidgetsHistory.Last().ZOrder;

	if(!CurrentWidget->IsInViewport())
	{
		CurrentWidget->AddToViewport(ZOrder);
	}

	return CurrentWidget;
}

void UWidgetsManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	OpenWidgetFromClass(StartWidgetClass, true, 0);
}
