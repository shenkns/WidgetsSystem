// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/WidgetsManagerComponent.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

UWidgetsManagerComponent::UWidgetsManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


UUserWidget* UWidgetsManagerComponent::OpenWidget(UUserWidget* Widget, bool bHideOld, int ZOrder)
{
	if(bHideOld)
	{
		for(UUserWidget* OldWidget : Widgets)
		{
			if(OldWidget)
			{
				OldWidget->RemoveFromParent();
			}
		}
	}

	if(!Widget) return nullptr;

	Widgets.AddUnique(Widget);
	CurrentWidget = Widget;

	CurrentWidget->AddToViewport(ZOrder);
	
	return CurrentWidget;
}

UUserWidget* UWidgetsManagerComponent::OpenWidgetFromClass(TSubclassOf<UUserWidget> Class, bool bHideOld, int ZOrder)
{
	if(!IsValid(Class)) return nullptr;

	if(UUserWidget* Widget = CreateWidget<UUserWidget, UWorld>(GetWorld(), Class, FName(FGuid::NewGuid().ToString())))
	{
		return OpenWidget(Widget, bHideOld, ZOrder);
	}

	return nullptr;
}

UUserWidget* UWidgetsManagerComponent::Back()
{
	if(Widgets.Num() <= 1) return nullptr;

	Widgets.RemoveAt(Widgets.Num() - 1);

	if(CurrentWidget)
	{
		CurrentWidget->RemoveFromParent();
	}
	
	CurrentWidget = Widgets.Last();

	if(!CurrentWidget->IsInViewport())
	{
		CurrentWidget->AddToViewport(0);
	}

	return Widgets.Last(0);
}

void UWidgetsManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	OpenWidgetFromClass(StartWidgetClass, true, 0);
}
