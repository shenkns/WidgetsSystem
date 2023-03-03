// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/WidgetsManagerComponent.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

UWidgetsManagerComponent::UWidgetsManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UWidgetsManagerComponent::OpenWidget(UUserWidget* Widget, bool bHideOld, int ZOrder)
{
	if(bHideOld && CurrentWidget)
	{
		CurrentWidget->RemoveFromParent();
	}

	if(!Widget) return;

	Widgets.AddUnique(Widget);
	CurrentWidget = Widget;

	Widget->AddToViewport(ZOrder);
}

UUserWidget* UWidgetsManagerComponent::OpenWidgetFromClass(TSubclassOf<UUserWidget> Class, bool bHideOld, int ZOrder)
{
	if(!IsValid(Class)) return nullptr;

	if(UUserWidget* Widget = CreateWidget<UUserWidget, APlayerController*>(UGameplayStatics::GetPlayerController(this, 0), Class))
	{
		OpenWidget(Widget, bHideOld, ZOrder);
		return Widget;
	}

	return nullptr;
}

UUserWidget* UWidgetsManagerComponent::Back()
{
	if(Widgets.Num() <= 1) return nullptr;

	Widgets.RemoveAt(Widgets.Num() - 1);

	OpenWidget(Widgets.Last(0), true);

	return Widgets.Last(0);
}

void UWidgetsManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	OpenWidgetFromClass(StartWidgetClass, true, 0);
}