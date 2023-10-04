// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/WidgetsManagerComponent.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

UWidgetsManagerComponent::UWidgetsManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

UUserWidget* UWidgetsManagerComponent::OpenWidget(UUserWidget* Widget, EWidgetOpenMethod OpenMethod, int ZOrder)
{
	if(!Widget) return nullptr;

	switch(OpenMethod)
	{
	case EWidgetOpenMethod::ClearHistory:
		{
			for(const FWidgetHistory& OldWidget : WidgetsHistory)
			{
				if(OldWidget.Widget)
				{
					OldWidget.Widget->RemoveFromParent();
				}
			}

			WidgetsHistory.Empty();
			
			break;
		}
		
	case EWidgetOpenMethod::HideAll:
		{
			for(const FWidgetHistory& OldWidget : WidgetsHistory)
			{
				if(OldWidget.Widget)
				{
					OldWidget.Widget->RemoveFromParent();
				}
			}

			break;
		}

	case EWidgetOpenMethod::HidePrevious:
		{
			if(UUserWidget* PreviousWidget = GetCurrentWidget())
			{
				PreviousWidget->RemoveFromParent();
			}

			break;
		}
	}

	WidgetsHistory.Add(FWidgetHistory(Widget, ZOrder));

	Widget->AddToViewport(ZOrder);
	
	return Widget;
}

UUserWidget* UWidgetsManagerComponent::OpenWidgetFromClass(TSubclassOf<UUserWidget> Class, EWidgetOpenMethod OpenMethod, int ZOrder)
{
	if(!IsValid(Class)) return nullptr;

	if(UUserWidget* Widget = CreateWidget<UUserWidget, UWorld>(GetWorld(), Class, FName(FGuid::NewGuid().ToString())))
	{
		return OpenWidget(Widget, OpenMethod, ZOrder);
	}

	return nullptr;
}

UUserWidget* UWidgetsManagerComponent::Back()
{
	if(WidgetsHistory.Num() <= 1) return nullptr;

	if(UUserWidget* ClosingWidget = GetCurrentWidget())
	{
		ClosingWidget->RemoveFromParent();
	}

	WidgetsHistory.RemoveAt(WidgetsHistory.Num() - 1);
	
	const FWidgetHistory OpenedPreviousWidgetElement = WidgetsHistory.Last();
	if(!OpenedPreviousWidgetElement.Widget) return nullptr;

	if(!OpenedPreviousWidgetElement.Widget->IsInViewport())
	{
		OpenedPreviousWidgetElement.Widget->AddToViewport(OpenedPreviousWidgetElement.ZOrder);
	}

	return OpenedPreviousWidgetElement.Widget;
}

UUserWidget* UWidgetsManagerComponent::GetCurrentWidget() const
{
	return WidgetsHistory.Last().Widget;
}

void UWidgetsManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	OpenWidgetFromClass(StartWidgetClass, EWidgetOpenMethod::ClearHistory, 0);
}
