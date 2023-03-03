// Fill out your copyright notice in the Description page of Project Settings.


#include "Libs/WidgetSystemLibrary.h"

#include "Components/WidgetManagerComponent.h"
#include "GameFramework/HUD.h"
#include "Kismet/GameplayStatics.h"

UWidgetManagerComponent* UWidgetSystemLibrary::GetWidgetManager()
{
	const auto World = GEngine->GameViewport->GetWorld();
	if(!World) return nullptr;
	
	const auto HUD = UGameplayStatics::GetPlayerController(World, 0)->GetHUD();
	if(!HUD) return nullptr;

	return HUD->FindComponentByClass<UWidgetManagerComponent>();
}

void UWidgetSystemLibrary::OpenWidget(UUserWidget* Widget, bool bHideOld, int ZOrder)
{
	const auto WidgetManager = GetWidgetManager();
	if(!WidgetManager) return;

	WidgetManager->OpenWidget(Widget, bHideOld, ZOrder);
}

UUserWidget* UWidgetSystemLibrary::OpenWidgetFromClass(TSubclassOf<UUserWidget> Class, bool bHideOld, int ZOrder)
{
	const auto WidgetManager = GetWidgetManager();
	if(!WidgetManager) return nullptr;

	return WidgetManager->OpenWidgetFromClass(Class, bHideOld, ZOrder);
}

UUserWidget* UWidgetSystemLibrary::Back()
{
	const auto WidgetManager = GetWidgetManager();
	if(!WidgetManager) return nullptr;

	return WidgetManager->Back();
}
