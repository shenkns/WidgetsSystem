// Fill out your copyright notice in the Description page of Project Settings.


#include "Libs/WidgetsSystemLibrary.h"

#include "Components/WidgetsManagerComponent.h"
#include "GameFramework/HUD.h"
#include "Kismet/GameplayStatics.h"

UWidgetsManagerComponent* UWidgetsSystemLibrary::GetWidgetManager()
{
	const auto World = GEngine->GameViewport->GetWorld();
	if(!World) return nullptr;
	
	const auto HUD = UGameplayStatics::GetPlayerController(World, 0)->GetHUD();
	if(!HUD) return nullptr;

	return HUD->FindComponentByClass<UWidgetsManagerComponent>();
}

UUserWidget* UWidgetsSystemLibrary::OpenWidget(UUserWidget* Widget, EWidgetOpenMethod OpenMethod, int ZOrder, bool Instant)
{
	const auto WidgetManager = GetWidgetManager();
	if(!WidgetManager) return nullptr;

	return WidgetManager->OpenWidget(Widget, OpenMethod, ZOrder, Instant);
}

UUserWidget* UWidgetsSystemLibrary::OpenWidgetFromClass(TSubclassOf<UUserWidget> Class, EWidgetOpenMethod OpenMethod, int ZOrder, bool Instant)
{
	const auto WidgetManager = GetWidgetManager();
	if(!WidgetManager) return nullptr;

	return WidgetManager->OpenWidgetFromClass(Class, OpenMethod, ZOrder, Instant);
}

UUserWidget* UWidgetsSystemLibrary::Back(bool Instant)
{
	const auto WidgetManager = GetWidgetManager();
	if(!WidgetManager) return nullptr;

	return WidgetManager->Back(Instant);
}
