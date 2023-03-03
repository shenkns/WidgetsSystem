// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/WidgetManagerComponent.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

UWidgetManagerComponent::UWidgetManagerComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void UWidgetManagerComponent::OpenWidget(UUserWidget* Widget, bool bHideOld, int ZOrder)
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

UUserWidget* UWidgetManagerComponent::OpenWidgetFromClass(TSubclassOf<UUserWidget> Class, bool bHideOld, int ZOrder)
{
	if(!IsValid(Class)) return nullptr;

	if(UUserWidget* Widget = CreateWidget<UUserWidget, APlayerController*>(UGameplayStatics::GetPlayerController(this, 0), Class))
	{
		OpenWidget(Widget, bHideOld, ZOrder);
		return Widget;
	}

	return nullptr;
}

UUserWidget* UWidgetManagerComponent::Back()
{
	if(Widgets.Num() <= 1) return nullptr;

	Widgets.RemoveAt(Widgets.Num() - 1);

	OpenWidget(Widgets.Last(0), true);

	return Widgets.Last(0);
}

void UWidgetManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	OpenWidgetFromClass(StartWidgetClass, true, 0);
}
